// D触发器的实现
// @param i_state 输入的状态，也就是下一个状态
// @param reset 重置信号
// @param clk 时钟信号
// @param o_state 输出的状态
module DFlipFlop(i_state, reset, clk, o_state);
    input [2:0]i_state;
    input reset, clk;
    output reg[2:0]o_state;
    always @(posedge clk) begin
        if (reset) o_state = 3'b000;
        else o_state = i_state;
    end
endmodule
