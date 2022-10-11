// 顶层模块的实现
module Main(CLK, RST, outside_pc, ins, now_pc);
  input CLK, RST;
  input [31:0] outside_pc;
  output [31:0] ins, now_pc;
  parameter endReg = 5'b11111; // 31号寄存器

  // 数据通路
  wire [31:0] pc, pc0, pc4, i_IR, instruction, pcChoose3, pcChoose1, extendData, ALUResult, WriteData, ReadData1, ReadData2, DataOut;
  wire [31:0] o_ADR, o_BDR, o_ALUout, i_ALUM2DR,i_ALUData1,i_ALUData2;
  wire zero;
  // 控制信号
  wire [2:0] ALUOp;
  wire [1:0] ExtSel, RegDst, PCSrc;
  wire PCWre, IRWre, InsMemRW, WrRegData, RegWre, ALUSrcB, DataMemRW, DBDataSrc;

  // 数据选择输出
  wire [4:0] fiveChooseData;
  wire [31:0] InputWriteData1;

  // 引脚输出
  assign ins = instruction;
  assign now_pc = pc0;

  PC PC(CLK, pc, PCWre, RST, outside_pc, pc0); // 添加了外部pc
  PCAddFour PCAddFour(pc0, pc4);
  InstructionMEM InstructionMEM(pc0, InsMemRW, i_IR); // 添加了外部pc
  IR IR(i_IR, CLK, IRWre, instruction);
  PCJump PCJump(pc0, instruction[25:0], pcChoose3);
  DataSelector_3to1 DataSelector_3to1(endReg, instruction[20:16], instruction[15:11], RegDst, fiveChooseData);
  RegFile RegFile(instruction[25:21], instruction[20:16], fiveChooseData, WriteData, RegWre, CLK, ReadData1, ReadData2);
  ADR ADR(ReadData1, CLK, o_ADR);
  BDR BDR(ReadData2, CLK, o_BDR);
  SignExtend SignExtend(instruction[15:0], ExtSel, extendData);
  DataSelector_2to1_sa DataSelector_2to1_1(o_ADR, instruction[10:6] , ALUSrcA, i_ALUData1);
  DataSelector_2to1 DataSelector_2to1_2(o_BDR, extendData, ALUSrcB, i_ALUData2);
  ALU ALU(i_ALUData1, i_ALUData2, ALUOp, zero, ALUResult);
  ALUoutDR ALUoutDR(ALUResult, CLK, o_ALUout);
  DataMEM DataMEM(o_BDR, o_ALUout, DataMemRW, DataOut);
  DataSelector_2to1 DataSelector_2to1_3(ALUResult, DataOut, DBDataSrc, i_ALUM2DR);
  DBDR DBDR(i_ALUM2DR, CLK, InputWriteData1);
  DataSelector_2to1 DataSelector_2to1_4(pc4, InputWriteData1, WrRegData, WriteData);
  PCAddImm PCAddImm(pc4, extendData, pcChoose1);
  DataSelector_4to1 DataSelector_4to1(pc4, pcChoose1, ReadData1, pcChoose3, PCSrc, pc);
  ControlUnit ControlUnit(instruction[31:26], CLK, RST, zero, PCWre, InsMemRW, IRWre, WrRegData, RegWre, ALUSrcA, ALUSrcB, DataMemRW, DBDataSrc, ExtSel, RegDst, PCSrc, ALUOp);
endmodule