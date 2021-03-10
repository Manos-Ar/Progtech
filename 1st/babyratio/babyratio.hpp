class rational{
public :
        rational(int n, int d);
	// rational(const rational &r);
        //rational ();

        rational add (rational r);
        rational sub (rational r);
        rational mul (rational r);
        rational div (rational r);


        void print ();
		
private :
         int nom , den;
//         int sign;
         static int gcd (int a, int b);
};
