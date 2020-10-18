
# Verilator + JTAG C model

PULP-Platform内の[JTAG DPI Module][(https://github.com/pulp-platform/jtag_dpi)は、SystemVerilog DPIを使って、ソフトウェアとソケット通信をすることで、JTAGの通信ができるものです。

Verilatorは、SystemVerilog DPIのimportはサポートしているものの、exportをサポートしていないのでこのままでは使えません。
そこで、C側のコード(jtag_dpi.c)をちょこっと変更し、Verilatorでも使えるようにしました。

ソフトウェア側では、ポート番号 4567 に繋いで、uint8_tのデータ(TCLK=BIT[0], TRSTN=BIT[1], TDI=BIT[2], TMS==BIT[3])を送ることでHDL側にJTAGの信号を通知します。HDLからのTDOはソフトウェア側からの獲得要求があったときのみ通知します。このプロトコルについては、jtag.c の jtag_recv関数の内容を確認してください。

