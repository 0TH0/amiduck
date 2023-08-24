●タイトル：Amida

●ジャンル：3Dあみだくじ

●制作期間 : 4か月

●動画URL
https://clipchamp.com/watch/mSqPpweCg7l

●開発環境
・ハードウェア : Windows(i7、メモリ32GB)
・開発用ＯＳ   : Windows10
・統合開発環境： Microsoft Visual Studio 2022
・開発言語    ：C, C++, HLSL
・ライブラリ   : directX11,FBXSDK

●操作方法
入力デバイス	：マウス、キーボード
 SPACE	:ジャンプ
   E      	:アイテム使用
左クリック	：木の板を出す
右クリック長押し：カメラ回転
　ホイール　　　：カメラ上下回転
  tab	 	 :カメラ切り替え

●アイテムの種類
・プレイヤーの周りを回る玉
・爆弾(正面に向かって進む爆弾)
・羽（移動速度が一定時間速くなる)

●敵のAI
赤：プレイヤーを追いかける
青：プレイヤーとの距離が30以下なら追いかける
緑：ランダムなマスを目指す

●ゲーム説明
・あみだくじに沿って進み、道にある星を５つ集めたら勝ち、赤青緑の玉に当たると負け
・敵が来たときはタイミングよくジャンプすると回避することができる
・左クリックで橋をだして進む道を予想して勝利を目指そう

●こだわり
・Engine/Astar.cpp
→Astar法によってキャラクターを追う敵を実装した

・Enemy/EnemyBase.cpp
→EnemyBaseを継承してEnemyRed,EnemyBlueクラスなどを実装した
→Enemyの移動に線形補間を使用してスムーズに動くようにした

・Stage/stage.cpp
→橋を出す位置が分かりやすいように透明の橋を表示させた

・Assets/Shader/Normalmap.hlsl
→シェーダーでノーマルマップを実装した

・Assets/Shader/WaterShader.hlsl
→uvスクロールによって海の流れを表現した

・Player/CharacterBase.cpp
→あみだくじに沿って進むキャラクターAIを実装した

・Engine/Global.h
→XMVECTORからXMFLOAT3の変換、距離の計算などのよく使用する関数を実装した

・Manager/GameManger.cpp
→GameMangerでゲームの進行を管理した。
→星の位置のランダム生成をして規則性をなくした

・Observer/ResultObserver.cpp
→ObserverパターンをResultに実装した

・Engine/BillBorad.cpp
→ビルボードを使ったエフェクトにこだわった

・Engine/Image.cpp
→画像クリックやフェード処理などのよく使う機能をクラスに追加した

・Engine/Model.cpp
→ステージに同じステージを何個も用意する為、フライウェイトパターンを使用した

・Engine/CsvReader.cpp
→ステージの情報をcsvに保存し、コードの可読性を意識した

・定数や変数などの命名規則を意識して組んだ
・モデル、UIの統一感にこだわった