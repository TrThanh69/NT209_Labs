.section .data
rg:
	.string "MinhThanh"
rg_len = . -rg
ns:
	.string "\n"
ns_len = . -ns

.section .text
	.globl _start
_start:
	// Quá trình tính độ dài 
	
		// Gán độ dài vào thanh ghi %eax
		movl $rg_len, %eax 	
		
		// Bỏ đi kí tự cuối /n
		subl $1, %eax 	
		
		// Chuyển đổi từ số (demical) sang chữ (dạng ascii)	
   		addl $48, %eax 		
   		
   		// Gán kết quả về biến len
		movl %eax, len 		

	//Output độ dài chuỗi ký tự
    	movl $1, %edx
    	movl $len, %ecx
    	movl $1, %ebx   
    	movl $4, %eax 
	int $0x80  
			
	//Hàng mới
	movl $ns_len, %edx
	movl $ns, %ecx
	movl $1, %ebx
	movl $4, %eax
	int $0x80
	
	//Thoát chương trình
    	movl $1, %eax 
    	int $0x80

.section .bss
	.lcomm len, 1  



