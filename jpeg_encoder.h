#ifndef __JPEG_ENCODER_HEADER__
#define __JPEG_ENCODER_HEADER__


class JpegEncoder
{
public:
	// Renew lại bộ đệm
	void clean(void);

	// Đọc dữ liệu ảnh BMP 24 bit deepth
	bool readFromBMP(const char* fileName);

	// Mã hóa thành ảnh JPEG
	bool encodeToJPG(const char* fileName, int quality_scale);

private:
	int				m_width;		// Chiều rộng
	int				m_height;		// Chiều cao
	unsigned char*	m_rgbBuffer;	// Mảng chứa toàn bộ điểm ảnh m_width*m_height*3
	
	unsigned char	m_YTable[64];	// Chứa độ sáng khi chuyển đổi không gian màu
	unsigned char	m_CbCrTable[64]; // Chứa độ màu khi chuyển đổi khôn gian màu

	// Một bitstring khi mã hóa sẽ được lưu dưới dạng 1 cặp giá trị (độ dài bit 0 bỏ qua, giá trị kế tiếp khác 0)
	struct BitString
	{
		int length;	
		int value;
	};

	// Mảng trung gian chứa các giá trị mã hóa khởi tạo ban đầu cho cây huffman
	BitString m_Y_DC_Huffman_Table[12];
	BitString m_Y_AC_Huffman_Table[256];

	BitString m_CbCr_DC_Huffman_Table[12];
	BitString m_CbCr_AC_Huffman_Table[256];

private:
	// Gọi đầu tiên. Khởi tạoc ác giá trị mặc định cho table
	void _initHuffmanTables(void);

	// Khởi tạo các thay đổi về chất lượng nén ảnh. Tham số càng lớn thì dung lượng ảnh nén càng nhỏ
	void _initQualityTables(int quality);

	// Được gọi khi đã init bảng Table. Khởi tạo ban đầu
	void _computeHuffmanTable(const char* nr_codes, const unsigned char* std_table, BitString* huffman_table);

	// Phương thứuc trả về số lượng bit cần tối thiểu để biểu diễn số nguyên value
	BitString _getBitCode(int value);

	// Chuyển đổi không gian màu từ RGB sang Y(Độ sáng) Cb Cr (Độ màu)
	void _convertColorSpace(int xPos, int yPos, char* yData, char* cbData, char* crData);

	// biến đổi cosin rời rạc 2 chiều
	void _foword_FDC(const char* channel_data, short* fdc_data);

	// Mã hóa huffman
	void _doHuffmanEncoding(const short* DU, short& prevDC, const BitString* HTDC, const BitString* HTAC,  BitString* outputBitString, int& bitStringCounts);

private:
	// ghi header file JPEG
	void _write_jpeg_header(FILE* fp);

	// Các bién thể của phương thức ghi xuống file
	void _write_byte_(unsigned char value, FILE* fp); // ghi lần 1 byte
	void _write_word_(unsigned short value, FILE* fp); // ghi lần 1 word (2 byte)
	void _write_bitstring_(const BitString* bs, int counts, int& newByte, int& newBytePos, FILE* fp); // ghi lần 1 đối tượng của mảng Bitstring theo số lượng biến count byte
	void _write_(const void* p, int byteSize, FILE* fp); // hia lần 1 byte nhưng đặc biệt để ghi header file

public:
	// Phương thức tạo và phương thức hủy
	JpegEncoder();
	~JpegEncoder();
};

#endif
