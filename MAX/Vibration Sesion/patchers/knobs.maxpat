{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 6,
			"revision" : 5,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 680.0, 577.0, 886.0, 666.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "c-info",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 20.0, 20.0, 247.0, 33.0 ],
					"text" : "Cambia la IP de udpsend a la IP del Arduino.\nEl botón envía /MB <M1> <M2> como floats."
				}

			}
, 			{
				"box" : 				{
					"id" : "c-m1",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 20.0, 70.0, 200.0, 20.0 ],
					"text" : "Motor 1 (M1)  -2..2 vueltas"
				}

			}
, 			{
				"box" : 				{
					"id" : "dial-m1",
					"maxclass" : "dial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 20.0, 95.0, 40.0, 40.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "scale-m1",
					"maxclass" : "newobj",
					"numinlets" : 6,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 70.0, 105.0, 110.0, 22.0 ],
					"text" : "scale 0 127 -2. 2."
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "num-m1",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 190.0, 105.0, 60.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "store-m1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 260.0, 105.0, 40.0, 22.0 ],
					"text" : "f 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "c-m2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 20.0, 150.0, 200.0, 20.0 ],
					"text" : "Motor 2 (M2)  -2..2 vueltas"
				}

			}
, 			{
				"box" : 				{
					"id" : "dial-m2",
					"maxclass" : "dial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 20.0, 175.0, 40.0, 40.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "scale-m2",
					"maxclass" : "newobj",
					"numinlets" : 6,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 70.0, 185.0, 110.0, 22.0 ],
					"text" : "scale 0 127 -2. 2."
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "num-m2",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 190.0, 185.0, 60.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "store-m2",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 260.0, 185.0, 40.0, 22.0 ],
					"text" : "f 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "btn-send",
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 20.0, 235.0, 100.0, 25.0 ],
					"text" : "ENVIAR /MB",
					"usebgoncolor" : 1,
					"usetextovercolor" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "t-bb",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 130.0, 235.0, 40.0, 22.0 ],
					"text" : "t b b"
				}

			}
, 			{
				"box" : 				{
					"id" : "pak-mb",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 320.0, 145.0, 80.0, 22.0 ],
					"text" : "pak 0. 0."
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "t-bb", 0 ],
					"source" : [ "btn-send", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "scale-m1", 0 ],
					"source" : [ "dial-m1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "scale-m2", 0 ],
					"source" : [ "dial-m2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "num-m1", 0 ],
					"order" : 1,
					"source" : [ "scale-m1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "store-m1", 0 ],
					"order" : 0,
					"source" : [ "scale-m1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "num-m2", 0 ],
					"order" : 1,
					"source" : [ "scale-m2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "store-m2", 0 ],
					"order" : 0,
					"source" : [ "scale-m2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "pak-mb", 0 ],
					"source" : [ "store-m1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "pak-mb", 1 ],
					"source" : [ "store-m2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "store-m1", 0 ],
					"source" : [ "t-bb", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "store-m2", 0 ],
					"source" : [ "t-bb", 1 ]
				}

			}
 ],
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
