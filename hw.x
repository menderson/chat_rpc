struct param {
        int arg1;
        int arg2;
};

program PROG {
	version VERS {
		string func0(void)   = 1;
		int    func1(string) = 2;
		int    func2(string) = 3;
		string func3(void)   = 4;

		int		 func4(void) = 5;
	} = 1;
} = 0x30009999;
