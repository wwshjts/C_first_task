int isDel(char ch){
	return ch <= ' ';
}

int isAlpha(char ch){
	int isLow = ('a' <= ch) && (ch <= 'z');
	int isBig = ('A' <= ch) && (ch <= 'z');
	int isDig = ('1' <= ch) && (ch <= '9');
	return isBig || isLow || isDig;
}
