======================== BATTLESHIP ========================


### Giới thiệu

Một trò chơi đơn giản được viết bằng C++ sử dụng SDL2 làm thư viện đồ họa. Đây là dự án làm game đầu tiên của tôi cho bài tập lớn môn Lập trình nâng cao. Tôi viết dự án của mình trên Window (64bit) bằng CodeBlocks IDE (64bit).

### Cài đặt

Để chạy chương trình và chơi game này, đầu tiên chúng ta cần tải và cài đặt CodeBlocks và thư viện SDL, SDL image và SDL font.
Tải và cài đặt thư viện SDL: https://www.libsdl.org/ (1)
SDL image, SDL font: https://www.libsdl.org/projects/SDL_image/release/ (2)
Với thư viện SDL (1), sau khi tải về:
Giải nén vào một thư mục nào đó, trong đó có 2 thư mục, chỉ dùng đến 01:
○ i686-w64-mingw32 dành cho CodeBlock 32 bit.
○ x86_64-w64-mingw32 dành cho CodeBlock 64 bit hoặc có compiler 64 bit.
++Các bước cài SDL:
Copy file dll ...\x86_64-w64-mingw32\bin\SDL2.dll vào thư mục mã nguồn project (nơi có các file .cpp).
Setting | Compiler | Linker Setting: chép vào Other Linker Option: -lmingw32 -lSDL2main -lSDL2
Setting | Compiler | SearchDirectory | Compiler: thêm vào Policy đường dẫn: ...\x86_64-w64-mingw32\include\SDL2
Setting | Compiler | SearchDirectory | Linker: thêm vào Policy đường dẫn: ...\x86_64-w64-mingw32\lib
Cài thư viện image, ttf, mix các bạn cũng làm tương tự cài SDL

### Cách chơi

Sau khi cài thư viện SDL xong bạn chỉ cần tải dự án của tôi rồi nhấn đúp vào `SDL_Lam_Game.cbp` để chạy trò chơi. Nhấn `UP`, `DOWN`, `LEFT`, `RIGHT` (phím mũi tên) để duy triển và bạn nhấn chuột trái hoặc phải để bắn đạn. Bạn cần bắn máy bay địch và né đạn của địch nếu bạn bị va chạm thì bạn sẽ mất máu. Game sẽ có các vật phẩm bổ trợ cho bạn