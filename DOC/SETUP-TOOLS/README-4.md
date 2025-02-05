Tools: 
    + Chương trình quản lý mô trường code và gói tin: [MSYS2](https://www.msys2.org/) dựa trên Linux
        ( Môi trường code [UCRT64](https://www.msys2.org/docs/environments/) )

    + VS code Insiders [VScode](https://code.visualstudio.com/insiders/)
        ( Extensions: C/C++ Extension Pack, GitLens, PlatformIO IDE, Makefile Tools , Python, Python Debugger, Code Runner)

    + Mô phỏng module proteus 8.16 [ Link Tải ](https://phanmem123.com/download-proteus/) [Thư viện](https://electronicstree.com/free-proteus-8-libraries/)
    + Mô phỏng nâng cao [ Renode ](https://renode.io/) (mã nguồn mở)

    + Thiết kế pcb: học thông qua KiCad 8.0, sử dụng cho đồ án thì EasyEda. 
    ( Kicad không bị giới hạn bên gia công, khi sài EasyEda thì chỉ có thể gia công pcb bên JLCpcb, EasyEda được làm ra dựa trên Kicad )

Setup MSYS2:
    - Sau khi đã tải về và cài đặt khi note lại vị trí cài đặt chương trình.
    - Cửa sổ ứng dụng hiện lên chay: " pacman -Syu " -> nhấn y với enter -> chương trình chạy xong sẽ tự động tắt 
    - Nhấn phím Window tìm "Edit the system variables " -> Path -> New -> "../msys64/ucrt64/bin" && "../msys64/usr/bin" 
    - Bật CMD/PowerShell/Terminal chạy pacman

    - Nếu đã nhận chạy " pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-python-pip make cmake git"


    [Tài liệu kham khảo](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain)



