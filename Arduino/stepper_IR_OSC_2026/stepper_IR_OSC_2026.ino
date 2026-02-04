#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <AccelStepper.h>

// constantes de los sensores
const int sharp1Pin = A0;
const int sharp2Pin = A1;

// ---------------- WiFi ----------------
const char* ssid     = "SoniCarpet";
const char* password = "SoniCarpet";

WiFiUDP Udp;
const unsigned int localPort = 8000;  // puerto donde escucha el Arduino para OSC

// IP del ordenador donde está Max/MSP (cámbialo)
IPAddress destIP(192, 168, 1, 102);
// Puerto en el que Max recibe OSC
const unsigned int destPort = 18000;

// ---------------- Motores ----------------
// Pines STEP y DIR del CNC Shield
AccelStepper stepper1(AccelStepper::DRIVER, 2, 5);  // Motor 1: X-axis
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6);  // Motor 2: Y-axis

const int enablePin   = 8;    // Pin Enable del CNC Shield
const int stepsPerRev = 200;  // ajusta si usas microstepping (ej. 3200)

// ---------- CONVERSIÓN BÁSICA GP2Y0A21 ----------


float rawAdcToCm(int adc) {
  if (adc < 10) adc = 10;  // evitar divisiones raras

  float cm = (6787.0 / (adc - 3.0)) - 4.0;

  // limitar al rango útil del sensor
  if (cm < 10.0) cm = 10.0;
  if (cm > 80.0) cm = 80.0;

  return cm;
}

// ---------- LECTURA ROBUSTA PARA UN SENSOR ----------
// id = 0 para sharp1, id = 1 para sharp2
float readDistanceCm(int pin, int id) {
  // 1) PROMEDIO (anti-ruido instantáneo)
  const int N = 25;   // sube a 40 si quieres aún más calma
  long sum = 0;

  for (int i = 0; i < N; i++) {
  sum += analogRead(pin);

  unsigned long t0 = millis();
  while (millis() - t0 < 2) {
    // NO BLOQUEA el resto del programa,
    // puedes poner aquí otras tareas si quieres
    // o dejarlo vacío
  }
}
  
  // for (int i = 0; i < N; i++) {
  //   sum += analogRead(pin);
  //   delay(2);
  // }
  int avgAdc = sum / N;

  float cm = rawAdcToCm(avgAdc);

  // 2) FILTRO EXPONENCIAL ADAPTATIVO (más suave cuanto más lejos)
  static float filt[2] = { -1.0, -1.0 };  // una memoria por sensor
  if (filt[id] < 0) {
    // primera lectura: inicializar
    filt[id] = cm;
    return cm;
  }

  float alpha;  // peso de la lectura nueva
  if (cm < 40.0) {
    alpha = 0.4;    // cerca: responde más rápido
  } else if (cm < 60.0) {
    alpha = 0.25;   // medio
  } else {
    alpha = 0.15;   // lejos: más suavizado (menos nervios)
  }

  filt[id] = alpha * cm + (1.0 - alpha) * filt[id];
  return filt[id];
}


// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);  // Desactivar motores al inicio (HIGH = disable)

  stepper1.setMaxSpeed(40.0); // steps/s
  stepper1.setAcceleration(40.0);  // steps/s^2

  stepper2.setMaxSpeed(40.0);
  stepper2.setAcceleration(40.0);

  // --- Conexión WiFi ---
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());

  // --- UDP para OSC ---
  Udp.begin(localPort);
  Serial.print("Escuchando OSC en puerto ");
  Serial.println(localPort);
  //destPort
  Serial.print("Enviando OSC de los IR al Puerto ");
  Serial.println(destPort);

  Serial.println("Mensajes OSC esperados:");
  Serial.println("  /M1 <float>   (vueltas motor 1)");
  Serial.println("  /M2 <float>   (vueltas motor 2)");
  Serial.println("  /MB <f> <f>   (vueltas M1 y M2)");
  Serial.println("Mensaje OSC enviado: /sharp, f, f:");
  
}

// ---------------- Loop ----------------
void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize > 0) {
    OSCMessage msg;
    while (Udp.available()) {
      msg.fill(Udp.read());
    }

    if (!msg.hasError()) {
      handleOSC(msg);
    } else {
      Serial.println("Error en mensaje OSC.");
    }
  }
  stepper1.run(); 
  stepper2.run();
  float d1 = readDistanceCm(sharp1Pin, 0);
  float d2 = readDistanceCm(sharp2Pin, 1);

  //   // Debug por Serial
  // Serial.print("S1: ");
  // Serial.print(d1, 1);
  // Serial.print(" cm   ||   S2: ");
  // Serial.print(d2, 1);
  // Serial.println(" cm");

  // Envío OSC: /sharp <d1> <d2>
  sendOscTwoFloats("/sharp", d1, d2);
  // Si quisieras hacer movimientos no bloqueantes,
  // aquí podrías llamar stepper1.run(); stepper2.run();
}

// ---------- FUNCIONES OSC ----------

// enviar un mensaje OSC con dos floats: /direccion v1 v2
void sendOscTwoFloats(const char* address, float v1, float v2) {
  OSCMessage msg(address);
  msg.add(v1);
  msg.add(v2);

  Udp.beginPacket(destIP, destPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

// ---------------- Lógica OSC ----------------
void handleOSC(OSCMessage &msg) {

  // /M1 <float>
  if (msg.fullMatch("/M1")) {
    if (msg.size() >= 1) {
      float revs = msg.getFloat(0);
      long targetPos = stepper1.currentPosition() + (long)(revs * stepsPerRev);

      Serial.print("OSC /M1 ");
      Serial.print(revs);
      Serial.println(" vueltas");

      digitalWrite(enablePin, LOW);  // Activar motores
      stepper1.runToNewPosition(targetPos);
      digitalWrite(enablePin, HIGH); // Desactivar motores

      Serial.println("M1 completado.");
    }
  }

  // /M2 <float>
  else if (msg.fullMatch("/M2")) {
    if (msg.size() >= 1) {
      float revs = msg.getFloat(0);
      long targetPos = stepper2.currentPosition() + (long)(revs * stepsPerRev);

      Serial.print("OSC /M2 ");
      Serial.print(revs);
      Serial.println(" vueltas");

      digitalWrite(enablePin, LOW);  // Activar motores
      stepper2.runToNewPosition(targetPos);
      digitalWrite(enablePin, HIGH); // Desactivar motores

      Serial.println("M2 completado.");
    }
  }

  // /MB <float> <float>
  else if (msg.fullMatch("/MB")) {
    if (msg.size() >= 2) {
      float revs1 = msg.getFloat(0);
      float revs2 = msg.getFloat(1);

      long targetPos1 = stepper1.currentPosition() + (long)(revs1 * stepsPerRev);
      long targetPos2 = stepper2.currentPosition() + (long)(revs2 * stepsPerRev);

      Serial.print("OSC /MB M1=");
      Serial.print(revs1);
      Serial.print(" M2=");
      Serial.println(revs2);

      digitalWrite(enablePin, LOW);  // Activar motores

      stepper1.moveTo(targetPos1);
      stepper2.moveTo(targetPos2);

      while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0) {
        stepper1.run();
        stepper2.run();
      }

      digitalWrite(enablePin, HIGH);  // Desactivar motores

      Serial.println("MB completado.");
    }
  }

  else {
    Serial.print("Dirección OSC desconocida: ");
    // no hay print de address directo en CNMAT, pero ya sabes que no coincide
    Serial.println("no coincide con /M1 /M2 /MB");
  }
}
