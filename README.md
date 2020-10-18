# みんなの SystemVerilog

今日(2020年10月17日)20時過ぎにちょこっと思い付いたのでgithubにアカウントを作り、このrepoを立ち上げました。

このrepoの目的は、SystemVerilogのコードをガンガン溜め込むことです。
非常に簡単な論理回路(and, or, nand, nor, not, Flipflopなど)やメモリから状態遷移マシン、Bus Functional
ModelなどSystemVerilogで書かれていれば何でもOKです。設計用の記述だけでなく、検証用の記述でもOKです。

## SystemVerilog の書籍

現在発行されているSystemVerilogに関する書籍

* [SystemVerilog入門](https://www.kyoritsu-pub.co.jp/bookdetail/9784320124639)、入門書というか LRM (Language Reference Manual)代わり
* [SystemVerilogによる検証の基礎](https://www.morikita.co.jp/books/book/3427)、上記「SystemVerilog入門」の著者によるSystemVerilogの検証に関するもの
* [SystemVerilog設計スタートアップ](https://www.cqpub.co.jp/hanbai/books/36/36191.htm)、2008年5月15日に出版されたCQ出版が過去発行していたDesign Wave Managineに掲載された記事を項目ごとにまとめたもの

## SystemVerilog に関するサイト

* [QiitaのSystemVerilog関連](https://qiita.com/search?q=SystemVerilog)
* [All of SystemVerilog](https://sites.google.com/site/allofsystemverilog/)、@Vengineer が大昔いろいろと書いたもの
  * 半導体ネットで連載しました[無償ツールで実践する「ハード・ソフト協調検証」(全8回)　(2009.12.6 - 2010.1.29)](https://sites.google.com/site/allofsystemverilog/Home/dpi-c)もあります

## いろいろなモデル

* [Models](Models.md)にいろいろなモデルへのリンクがあります

## SystemVerilogが利用できるシミュレータ 
### オープンソースソフトウェア
* [iverilog](http://iverilog.icarus.com/)
  * iverilogは、Verilog HDLのシミュレータであるが、オプションを付けると SystemVerilog の一部の機能が使えるようです
  * -g2012 というオプションを付けると、SystemVerilog 2012 をサポートするらしい
* [verilator](https://www.veripool.org/wiki/verilator)
  * verilator は、initial文をサポートしていません。その代わりに、C/C++/SystemCを使ってテストベンチ側を作ることができます

### FPGA開発環境で利用できるシミュレータ
* [Xilinx Simulator](https://japan.xilinx.com/products/design-tools/vivado/simulator.html)
  * SystemVerilogの多くの機能をサポートしている(UVMもサポートしている)
  * DPI (Direct Programming Interface)は、export task をサポートしていないので C 側から SystemVerilog 側の task が呼べないのが辛いです
* [Intel FPGA用ModelSim](https://www.intel.co.jp/content/www/jp/ja/software/programmable/quartus-prime/model-sim.html)
  * Mentor Graphics の ModelSim なので、Verilog HDL/VHDL/SystemVerilog をサポートしています
  * 無償バージョンではHDLの行数が制限や実行速度がかなり遅くなっています
  * Linux版は64ビットバージョンではなく、32ビットバージョンなのでLinux 側に32ビットのパッケージをインストールする必要があります

### お高いシミュレータ
* Synopsys VCS
* Cadence ISU/Xcelium
* Mentor Graphics Questa
* Aldec Riviera-PRO

また、[EDA Playgroud](https://www.edaplayground.com/)に登録すると、いろいろなSimulatorが利用できます。



