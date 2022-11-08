# Manual_Vzense_DCAM710
VzenseSDK_Windowsを使って得たVCAM710の深度情報をUnityに送る。


## VzenseSDKの動かし方
	
- 環境  
	Windows 11  
	Visual Studio 2019  
	OpenCV3.0.0  
	
- 参考にしたページ  
	[Visual StudioでOpenCVを使う方法](https://betashort-lab.com/%e3%83%97%e3%83%ad%e3%82%b0%e3%83%a9%e3%83%9f%e3%83%b3%e3%82%b0/cpp/visual-studio%e3%81%a7opencv%e3%82%92%e4%bd%bf%e3%81%86%e6%96%b9%e6%b3%95/)  
	[VisualStudio2019+OpenCVのデバッグでDLLが見つからない](https://qiita.com/oppuna/items/4c13ae7d33db46cc69b4)

### 手順
1. VzenseのSDK(Vzense_SDK_Windows)を[GitHub](https://github.com/Vzense/Vzense_SDK_Windows)からダウンロードする（uec-media-design-lab/Manual_Vzense_DCAM710/Vzense SDKを使用しても良い。）
	- 展開する
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135303938373733352e706e67-700x333.png)
	
1. [OpenCV3.0.0](https://opencv.org/releases/page/6/)をダウンロードする
	- 他Verでも動かせるけど、用意されたsdkは3.0.0を使っていて設定変えるのが大変なので3.0.0を使う。
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135313136373337332e706e67-700x257.png)

	- Cドライブ直下に配置(他verのOpenCVと競合しないよう注意)
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135313437333031372e706e67-700x226.png)
	- パスを通しておく（多分x86の方だけでいい）
	`C:\opencv\build\x64\vc12\bin`
	`C:\opencv\build\x86\vc12\bin`
![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135313935303530352e706e67-700x237.png)

1. Vzense_SDK_WindowsのSample.slnをVisual Studioで開く
	- 多分↓はOKで良い  
![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135323530393039322e706e67.png)
	- DCAM710以外は使わないので消しとく。(残してるとうまくビルドできないときがある)
![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135323538373035392e706e67-700x447.png)

1. Frame_Viewer_DCAM710.cppを開く
	- この時点ではOpenCVがうまくincludeされていない
![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135323830333431332e706e67-700x219.png)

1. プロパティページを編集
	- 上部メニューのプロジェクト＞プロパティ＞C/C++＞全般＞追加のインクルードディレクトリに`C:\opencv\build\include`と設定する
	![file](https://uecmediadesign.synology.me/wordpress/wp-content/uploads/2022/04/image-1651153485760.png)
	- プロジェクト＞プロパティ＞リンカー＞全般＞追加のライブラリディレクトリに`C:\opencv\build\x86\vc12\lib;C:\opencv\build\x86\vc12\staticlib`と設定
	（※リンカーの欄が無い場合は一度ビルドしてみると表示されるかも？）
	![file](https://uecmediadesign.synology.me/wordpress/wp-content/uploads/2022/04/image-1651153840993.png)
	- プロジェクト＞プロパティ＞リンカー＞入力＞追加の依存ファイルを「[追加の依存ファイル](https://uecmediadesign.synology.me/wordpress/wp-content/uploads/2022/04/追加の依存ファイル.txt "追加の依存ファイル")」の内容で上書きする。(C:\opencv\build\x86\vc12以下にある.libファイルをすべて追加している)
![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135343135393137382e706e67-700x402.png)
	- プロジェクト＞プロパティ＞ビルドイベント＞ビルド後のイベント＞コマンドラインに書いてある内容を全て消す。
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135343434383633352e706e67.png)
	- 消していいのか正直よくわかっていないが、これがあると↓のエラーになる。ビルド後に何かファイルをコピーするためのものらしいが、とりあえず消しても問題なさそう。
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313135343337333433332e706e67-1-700x49.png)

1. ビルドして実行する
	- サンプルが動く
	![file](https://uecmediadesign.synology.me/wordpress/wp-content/uploads/2022/04/image-1651154743266.png)

### 動作の様子

- あとはサンプルコードを都度書き換えれば深度情報とか表示できそう。
	- ↓コンソールに中心の深度情報を表示してみた。
	![file](https://uecmediadesign.synology.me/wordpress/wp-content/uploads/2022/04/image-1651155309731.png)


## UnityとのUDP通信

- 参考にしたページ  
	[C++とUnity(C#)を使ったUDP通信](https://trollface.hatenablog.com/entry/2019/02/17/162042)

### 手順
1. C++側での送信プログラム
	- UDP.cppとUDP.h(uec-media-design-lab/Manual_Vzense_DCAM710/Vzense SDK/Samples/FrameViewer_DCAM710/)をプロジェクトに新規で作成する。（Send()関数）
![image](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/181468547-9f76b67f-6702-4ab8-acdd-f69b64b3e1a5-700x313.png)

1. プロパティの設定
	- プロジェクト＞プロパティ＞リンカー＞入力＞追加の依存ファイルに`ws2_32.lib`を追加する。(UDP/TCP通信用)
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313232383134373533362e706e67.png)
	- 上部メニューのプロジェクト＞プロパティ＞C/C++＞全般＞追加のインクルードディレクトリに`./`を追加する
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313232383035303139352e706e67-700x245.png)
		- これをしないとincludeできない
		![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313232373937363034332e706e67.png)

1. Unity側での受信プログラム
	- 空オブジェクトを作ってUDPReceive(uec-media-design-lab/Manual_Vzense_DCAM710/Unity_Script/UDPReceive.cs)スクリプトをアタッチする
	![file](https://www.media.lab.uec.ac.jp/wp-content/uploads/2022/08/68747470733a2f2f7565636d6564696164657369676e2e73796e6f6c6f67792e6d652f776f726470726573732f77702d636f6e74656e742f75706c6f6164732f323032322f30342f696d6167652d313635313232383234353733392e706e67-700x128.png)

1. 動かす
	- send関数が呼ばれるとC++側からUDP通信で深度情報が送られる。
	- 深度情報を使ったアプリケーションを作成できる。
