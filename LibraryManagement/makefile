CC = gcc
CFLAGS = -I./book -I./user -I./management -I./utils -Wall -Wextra

#Các file nguồn
SRC = main.c \
      book/book.c \
      user/user.c \
      management/management.c \
      utils/utils.c

#File đích
TARGET = output/library.exe

#Quy tắc mặc định
all: $(TARGET)

#Biên dịch ra file thực thi
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

#Quy tắc dọn dẹp
clean:
	del /Q $(TARGET) 2>nul || echo Đã dọn dẹp.
