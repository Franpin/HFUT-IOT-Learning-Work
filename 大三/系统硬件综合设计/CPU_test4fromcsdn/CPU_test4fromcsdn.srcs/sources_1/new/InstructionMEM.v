// 指令存储单元的实现
// @param InsMemRW 指令存储单元信号
// @param addr pc上指令的地址
// @param outside_pc 获取初始化的pc
// @param instruction 取得的指令
module InstructionMEM (addr, InsMemRW, instruction);
    input InsMemRW;
    input [31:0] addr;
    output reg [31:0] instruction;
    // 8位内存单元，每条指令的二进制代码占四个内存单元
    reg [7:0] mem [0:127];
     initial begin
     //$readmemb("D:/Xilinx/VivadoProject/MulticycleCPU/instructions.txt", mem); 
         mem[0]=8'b11100000;
         mem[1]=8'b00000000;
         mem[2]=8'b00000000;
         mem[3]=8'b00000010;
         mem[4]=8'b11100111;
         mem[5]=8'b11100000;
         mem[6]=8'b00000000;
         mem[7]=8'b00000000;
         mem[8]=8'b00001000;
         mem[9]=8'b00000001;
         mem[10]=8'b00000000;
         mem[11]=8'b00000100;
         mem[12]=8'b00001000;
         mem[13]=8'b00000010;
         mem[14]=8'b00000000;
         mem[15]=8'b00001000;
         mem[16]=8'b11000000;
         mem[17]=8'b01000010;
         mem[18]=8'b00000000;
         mem[19]=8'b00000000;
         mem[20]=8'b00000000;
         mem[21]=8'b01000001;
         mem[22]=8'b00011000;
         mem[23]=8'b00000000;
         mem[24]=8'b00000100;
         mem[25]=8'b01100001;
         mem[26]=8'b00011000;
         mem[27]=8'b00000000;
         mem[28]=8'b11010000;
         mem[29]=8'b01000011;
         mem[30]=8'b11111111;
         mem[31]=8'b11111110;
         mem[32]=8'b01001000;
         mem[33]=8'b00100001;
         mem[34]=8'b00000000;
         mem[35]=8'b00000001;
         mem[36]=8'b01000000;
         mem[37]=8'b01000001;
         mem[38]=8'b00011000;
         mem[39]=8'b00000000;
         mem[40]=8'b00000000;
         mem[41]=8'b01000000;
         mem[42]=8'b00011000;
         mem[43]=8'b00000000;
         mem[44]=8'b01000100;
         mem[45]=8'b01100010;
         mem[46]=8'b00001000;
         mem[47]=8'b00000000;
         mem[48]=8'b01100000;
         mem[49]=8'b00000010;
         mem[50]=8'b00001000;
         mem[51]=8'b10000000;
         mem[52]=8'b10011000;
         mem[53]=8'b00100010;
         mem[54]=8'b00110000;
         mem[55]=8'b00000000;
         mem[56]=8'b10011000;
         mem[57]=8'b01000001;
         mem[58]=8'b00111000;
         mem[59]=8'b00000000;
         mem[60]=8'b10011100;
         mem[61]=8'b00100110;
         mem[62]=8'b00000000;
         mem[63]=8'b00000001;
         mem[64]=8'b10011100;
         mem[65]=8'b11000111;
         mem[66]=8'b00000000;
         mem[67]=8'b00000001;
         mem[68]=8'b11101000;
         mem[69]=8'b00000000;
         mem[70]=8'b00000000;
         mem[71]=8'b00000001;
         mem[72]=8'b11000100;
         mem[73]=8'b01000100;
         mem[74]=8'b00000000;
         mem[75]=8'b00000000;
         mem[76]=8'b11111100;
         mem[77]=8'b00000000;
         mem[78]=8'b00000000;
         mem[79]=8'b00000000;
        instruction = 0;
     end
    always @(addr or InsMemRW)
        if (InsMemRW) begin
          instruction[31:24] = mem[addr];
          instruction[23:16] = mem[addr+1];
          instruction[15:8] = mem[addr+2];
          instruction[7:0] = mem[addr+3];
        end
endmodule