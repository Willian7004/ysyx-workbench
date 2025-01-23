#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Vour.h"
#include "verilated.h"

#include "verilated_vcd_c.h" //可选，如果要导出vcd则需要加上

VerilatedContext* contextp = new VerilatedContext;

Vour* top = new Vour{contextp}; 

void single_cycle() {
  top->clk = 0; top->eval();
  top->clk = 1; top->eval();
}

void reset(int n) {
  top->rst = 1;
  while (n -- > 0) single_cycle();
  top->rst = 0;
}



int main(int argc, char** argv) {
    contextp->commandArgs(argc, argv); 
    reset(10);  // 复位10个周期
    VerilatedVcdC* tfp = new VerilatedVcdC; //初始化VCD对象指针
    contextp->traceEverOn(true); //打开追踪功能
    top->trace(tfp, 0); //
    tfp->open("wave.vcd"); //设置输出的文件wave.vcd
    
    int i=0;
    while (!contextp->gotFinish()&& i<50) {
        single_cycle(); 

        tfp->dump(contextp->time()); //dump wave
        contextp->timeInc(1); //推动仿真时间
        i++;
        }
    delete top;
    tfp->close();
    delete contextp;
    return 0;
}
