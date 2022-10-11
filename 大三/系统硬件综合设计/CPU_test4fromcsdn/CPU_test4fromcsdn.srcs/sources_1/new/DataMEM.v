// 数据存储器的实现
// @param i_data 输入的数据
// @param addr 输入的地址
// @param DataMemRW 输入数据存储器的信号，用1代表/WR信号，用0代表/RD信号，我将这两个信号合为一个
// @param o_data 读取的数据
module DataMEM (i_data, addr, DataMemRW, o_data);
    input [31:0] i_data;
    input [31:0] addr;
    input DataMemRW;
    output reg [31:0] o_data;
    reg [7:0] memory [0:63];
     initial begin
        o_data = 0;
     end
      // 使用大端方式储存，这里有更改（不需要乘4）
    always @(addr or i_data or DataMemRW) begin
      if (DataMemRW) begin // 1 为 /WR
          memory[addr] = i_data[31:24];
          memory[addr+1] = i_data[23:16];
          memory[addr+2] = i_data[15:8];
          memory[addr+3] = i_data[7:0];
      end else begin // 0 为 /RD
          o_data[31:24] = memory[addr];
          o_data[23:16] = memory[addr+1];
          o_data[15:8] = memory[addr+2];
          o_data[7:0] = memory[addr+3];
      end
    end
endmodule 
