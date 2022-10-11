// 控制单元CU的实现
// @param opcode 操作码
// @param zero 输入的zero信号
// @param clk 时钟信号
// @param reset 重置信号
// @param PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcB, DataMemRW, ALUM2Reg，ExtSel, RegOut, PCSrc，ALUOp 控制信号
module ControlUnit(opcode, clk, reset, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcA, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);
    input [5:0]opcode;
    input zero, clk, reset;
    output PCWre, InsMemRW, IRWre, WrRegData, RegWre,ALUSrcA, ALUSrcB, DataMemRW, ALUM2Reg;
    output [1:0]ExtSel, RegOut, PCSrc;
    output [2:0]ALUOp;

    wire [2:0]i_state, o_state;

    DFlipFlop DFlipFlop(i_state, reset, clk, o_state);
    NextState NextState(o_state, opcode, i_state);
    OutputFunc OutputFunc(o_state, opcode, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcA, ALUSrcB, DataMemRW, ALUM2Reg, ExtSel, RegOut, PCSrc, ALUOp);

endmodule
