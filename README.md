# みんなの SystemVerilog

今日(2020年10月17日)20時過ぎにちょこっと思い付いたのでgithubにアカウントを作り、このrepoを立ち上げました。

このrepoの目的は、SystemVerilogのコードをガンガン溜め込むことです。
非常に簡単な論理回路(and, or, nand, nor, not, Flipflopなど)やメモリから状態遷移マシン、Bus Functional
ModelなどSystemVerilogで書かれていれば何でもOKです。設計用の記述だけでなく、検証用こ記述でもOKです。

## SystemVerilog の書籍

現在発行されているSystemVerilogに関する書籍

- [SystemVerilog入門](https://www.kyoritsu-pub.co.jp/bookdetail/9784320124639)、入門書というか LRM (Language Reference Manual)代わり１
- [SystemVerilogによる検証の基礎](https://www.morikita.co.jp/books/book/3427)、上記「SystemVerilog入門」の著者によるSystemVerilogの検証に関するもの
- [SystemVerilog設計スタートアップ](https://www.cqpub.co.jp/hanbai/books/36/36191.htm)、2008年5月15日に出版されたCQ出版が過去発行していたDesign Wave Managineに掲載された記事を項目ごとにまとめたもの

## SystemVerilog に関するサイト

- [QiitaのSystemVerilog関連](https://qiita.com/search?q=SystemVerilog)
- [All of SystemVerilog](https://sites.google.com/site/allofsystemverilog/)、@Vengineer が大昔いろいろと書いたもの
-- 半導体ネットで連載しました無償ツールで実践する「ハード・ソフト協調検証」(全8回)　(2009.12.6 - 2010.1.29)もあります

## SystemVerilogが利用できるシミュレータ 
### オープンソースソフトウェア
- [iverilog](http://iverilog.icarus.com/)
- [verilator](https://www.veripool.org/wiki/verilator)

### FPGA開発環境で利用できるシミュレータ
- [Xilinx Simulator](https://japan.xilinx.com/products/design-tools/vivado/simulator.html)
- [Intel FPGA用ModelSim](https://www.intel.co.jp/content/www/jp/ja/software/programmable/quartus-prime/model-sim.html)

### お高いシミュレータ
- Synopsys VCS
- Cadence ISU
- Mentor Graphics Questa
- Aldec Riviera-PRO

また、[EDA Playgroud](https://www.edaplayground.com/)に登録すると、いろいろなSimulatorが利用できます。



