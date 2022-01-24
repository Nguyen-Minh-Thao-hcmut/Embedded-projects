module read_ultrasonic_sensor(clk, EchoPulse, Trigger, D);// Lam sao de viet nhieu module con va trong module chinh goi module con?
input clk, EchoPulse;
output Trigger;
reg Trigger = 1'b1;
output [15:0]D;//Khi mo phong khong hieu gia tri hien thi la gi?
reg [15:0]D = 16'h0000;
reg [15:0]time_cnt = 16'h0000;
reg pre_pulse = 0;
reg [15:0]tmp = 16'h0000;
always @(posedge clk) begin
	time_cnt <= time_cnt + 1'b1;
	if (time_cnt == 16'h03e8) begin
		time_cnt <= 16'h0000;
		Trigger <= 1;
		D <= 16'h0000;
		end
	else if (16'h000a <= time_cnt < 16'h03e8) begin
		Trigger <= 0;
		pre_pulse <= EchoPulse;
		case ({pre_pulse, EchoPulse})
		2'b01: 
			begin
				if (tmp < 16'hffff)
					tmp <= tmp + 1'b1;
			end
		2'b11: 
			begin
				if (tmp < 16'hffff)
					tmp <= tmp + 1'b1;
			end
		2'b10:
			begin
				D <= tmp;
				tmp <= 16'h0000;
			end
		endcase
		end
	end
endmodule
