# AngelScriptAPIDoc
Generated the Angelscript for Unreal Engine API doc with easy way.
简单生成 Angelscript for Unreal Engine API 本地文档 

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

Section D:
本项目需要使用 https://github.com/Hazelight/UnrealEngine-Angelscript 的 UE 引擎，从UE官方安装的引擎是不能使用的。因为我使用的是最新的 5.5.4版本，需要自行修改插件和项目的引擎版本号。
比如，如果你使用的是　5.4.0 版本的引擎，需要修改项目与插件的版本为5.4.0 。
也可以使用 https://github.com/franklzt/UnrealEngine-Angelscript 的 UE 引擎，不过需要自己编译引擎。该分支加了方便的批处理文件用于编译本地版本，包括服务端，客户端，Android。
同时，需要的工具 https://www.naturaldocs.org/，请自行安装，之后再加入 path 的环境变量中，以保证可以全局使用 NaturalDocs.exe 来生成 API　文档。

1. 项目主要用于是提供 AngelScript API 的本地文档。 可以从 Release 中下载HTML.Zip文件直接使用。 
2. 如果想要自己制作 API 文档。可以下载此项目，编译后，打开后点工具栏的黄色按钮。参考下面最后一张图，完成后，复制项目中的 Docs 文件夹到 Plugins\AngelScriptAPIDoc\NatureDoc 目录下。
3. 双击 Plugins\AngelScriptAPIDoc\NatureDoc\GenerateDoc.bat,等待完成。
4. 打开 Plugins\AngelScriptAPIDoc\NatureDoc\HTML\index.html 就可以使用了.
 

<p align="center">
  <img src="ReadMe.png" alt="Off line doc Index">
</p>

<p align="center">
  <img src="Toolbar_GenerateDoc_Button.png" alt="Generate button in toolbar ">
</p>

