.section .data
la_doan_vien:
    .string "\nThuoc tuoi Doan\n"
la_doan_vien_len = .-la_doan_vien

Khong_la_doan_vien:
    .string "\nKhong thuoc tuoi Doan\n"
Khong_la_doan_vien_len = .-Khong_la_doan_vien

output_nhap:
    .string "Enter a year: "
output_nhap_len = .-output_nhap

Tuoi:
    .string "Your age is: "
Tuoi_len = .-Tuoi

.section .bss
    .lcomm input, 5
    .lcomm kq, 2
 
.section .text
    .globl _start

_start:
    //Output: "Enter a year: "
    movl $output_nhap_len, %edx
    movl $output_nhap, %ecx
    movl $1, %ebx
    movl $4, %eax
    int $0x80
    
    //Input: Nhập năm sinh
    movl $5, %edx
    movl $input, %ecx
    movl $0, %ebx
    movl $3, %eax
    int $0x80

	//Quá trình tính toán
    //chuyển input vào %ecx với input là định dạng xyzt
    movl $input, %ecx

    //xử lý kí tự đầu tiên: hàng nghìn
    movb (%ecx), %dl
    movzbl %dl, %edx
    subl $48, %edx
 
    //%eax = %eax * %edx = 10 * %edx
    mov $10, %eax
    imull %edx

    //chuyển số "hàng nghìn - x000" từ %eax vào %edx
    movl %eax, %edx

    //xử lý kí tự thứ 2: hàng trăm
    movb 1(%ecx), %bl
    movzbl %bl, %ebx
    subl $48, %ebx

    //Cộng hàng trăm vào hàng nghìn
    addl %ebx, %edx

    //%eax = %eax * %edx = 10 * %edx
    mov $10, %eax
    imull %edx

    //chuyển số "hàng trăm + nghìn - xy00" từ %eax vào %edx
    movl %eax, %edx

    //xử lý kí tự thứ 3: hàng chục
    movb 2(%ecx), %bl
    movzbl %bl, %ebx
    subl $48, %ebx

    //cộng hàng chục vào hàng nghìn và hàng trăm
    addl %ebx, %edx

    //%eax = %eax * %edx = 10 * %edx
    mov $10, %eax 
    imull %edx 

    //chuyển số "hàng chục + trăm + nghìn - xyz0" từ %eax vào %edx
    movl %eax, %edx

    //Xử lý kí tự cuối cùng: hàng đơn vị
    movb 3(%ecx), %bl
    movzbl %bl, %ebx
    subl $48, %ebx

    //cộng hàng đơn vị vào tổng trên
    addl %ebx, %edx

    //Trừ số tuổi - tính từ năm 2022
    movl $2022, %eax
    subl %edx, %eax

    //Gọi hàm Hien_tri_tuoi
    movl %eax, %edi
    call _Hien_tri_tuoi

    //Truyền số tuổi từ %edi sang $eax để só sánh
    movl %edi, %eax

    //So sánh tuổi với 15, nếu bé hơn hoặc bằng thì nhảy đến nhãn không thuộc đoàn
    cmpl $15, %eax
    jle _NO

    //So sánh với tuổi 30, nếu bé hơn hoặc bằng thì nhảy đến nhãn thuộc đoàn
    cmpl $30, %eax
    jle _YES

_NO:    
    //Tuổi không thuộc khoản từ 16 đến tròn 30 
    movl $Khong_la_doan_vien_len, %edx
    movl $Khong_la_doan_vien, %ecx

    //Thoát
    jmp _exit

_YES:
    //Tuổi thuộc khoản từ 16 đến tròn 30 
    movl $la_doan_vien_len, %edx
    movl $la_doan_vien, %ecx

    //Thoát
    jmp _exit

_Hien_tri_tuoi:
    //mở hàm
    pushq %rbp
    movq  %rsp, %rbp

    // clear giá trị thanh ghi
    xor %edx, %edx

    // chuyển số đã chia vào %eax
    movl %edi, -4(%rbp)
    movl -4(%rbp), %eax

    // chuyển số chia to %ecx (= 10)
    mov $10, %ecx
    div %ecx

    /// phần còn lại trong %edx, kết quả trong %eax
    addl $48, %edx
    addl $48, %eax

    // lưu số vào bộ nhớ để hiển thị
    movl $kq, %ebx
    movl %eax, (%ebx)
    movl %edx, 1(%ebx)

   //In ra "Your age is: "
    movl $Tuoi_len, %edx
    movl $Tuoi, %ecx
    movl $1, %ebx
    movl $4, %eax
    int $0x80

    //In số tuổi - Kết quả
    movl $2, %edx
    movl $kq, %ecx
    movl $1, %ebx
    movl $4, %eax
    int $0x80

    //kết thúc hàm
    popq %rbp
    ret

_exit:
    movl $1, %ebx
    movl $4, %eax
    int $0x80
    
    //Thoát chương trình
    movl $1, %eax
    int $0x80


