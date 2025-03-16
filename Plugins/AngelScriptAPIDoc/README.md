# AngelScriptAPIDoc
Generated the Angelscript for Unreal Engine API doc with easy way.

Section A:
If you just want to use the API doc 
You can download the zip doc from release or clone this repository, unzip HTML.zip under Plugins\AngelScriptAPIDoc\NatureDoc\HTML\and open Plugins\AngelScriptAPIDoc\NatureDoc\HTML\index.html and Enjoy the offline doc.
Please noted that I am using 5.5.4 version

Section B:
If you want to Manually generate the api doc 
Install the NatureDoc tool from https://www.naturaldocs.org/ and add it to environment varible path so that you can access the NaturalDocs.exe globally
For AngelScript for Unreal Engine,you can Install the Binary version or source code version from https://github.com/Hazelight/UnrealEngine-Angelscript.
If you are using binary version, you need to modify the version id to 5.4.0 for example of this plugin if you are using the 5.4.0 version of the Engine.

1. Download or git clone this project and compile the project.Please noted that this project do not work for engine installed from launcher.
2. Click the Button on toolbar in yellow,please refer to picture below and waiting until finished.
3. Copy the Generated Docs folder of this project to Plugins\AngelScriptAPIDoc\NatureDoc folder.
4. Double Click the Plugins\AngelScriptAPIDoc\NatureDoc\GenerateDoc.bat,waiting until finished.
5. Open the Plugins\AngelScriptAPIDoc\NatureDoc\HTML\index.html and and Enjoy the offline doc.

Section C:
If you want to Manually generate the api doc from your own project
1. Copy the Plugins folder to your project.
2. Reference to Section B step from 2. to 5.  

<p align="center">
  <img src="ReadMe.png" alt="Off line doc Index">
</p>

<p align="center">
  <img src="Toolbar_GenerateDoc_Button.png" alt="Generate button in toolbar ">
</p>