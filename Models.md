# いろいろなモデル


* https://github.com/taichi-ishitani/tnoc
    * SV で実装した NoC のルーターと AXI アダプター
    * UVM ベースの検証環境もあり
* https://github.com/taichi-ishitani/tbcm
    * FIFO や MUX などよく使いそうな基本モジュール集
    * `parameter type` を使って、より SV っぽくしてます
* https://github.com/taichi-ishitani/tvip-axi
    * AXI の VIP (モドキ)
    * UVM で実装
* https://github.com/taichi-ishitani/tvip-apb
    * APB の VIP (モドキ)
    * UVM で実装
* https://github.com/taichi-ishitani/tue
    * UVM で足りない部分や、バグ修正した拡張パッケージ
    * tvip-axi/tvip-apb のベース
