module cpu_sim;

    // Inputs
    reg CLK;
    reg RST;
    reg [31:0] outside_pc;

    // Outputs
    wire [31:0] ins, now_pc;

    // Instantiate the Unit Under Test (UUT)
    Main uut (
        .CLK(CLK), 
        .RST(RST), 
        .outside_pc(outside_pc), 
        .ins(ins),
        .now_pc(now_pc)
    );

    initial begin
        // Initialize Inputs
      CLK = 0;
      RST = 1;
      outside_pc = 0; // ���������ⲿpc
      #5; // �տ�ʼ����pcΪ0
          CLK = !CLK;
      #5;
          RST = 0;
      forever #10 begin // ����ʱ���ź�
          CLK = !CLK;
      end
    end
endmodule