#ifndef CALCULATION_H
#define CALCULATION_H

double cal(string term, float x)
{
    termComponents var;
    var.categorizeTerm(term);

    array<string> term_sep = operation(term); //operation between each term

    array<string> n_sep = operation(var.n); //operation between each n

    double result = 0, n = 0, u = 0, e = 0;
    double a = parseNum(term);

    for (unsigned short i = 0; i < var.n.length; i++) // 3x^2sin(3x)
    {
        double a_n = parseNum(var.n);
        string n_n = "";
        array<string> n_operate = operation(var.n); //ดูก่อน

        if (var.n[i] == 'x' && var.n[i + 1] == '^') // x^{3x^2}     //power
        {
            int sliceStart = i + 2; // number next to '^'
            i++;                    //skip ^
            while (isNum(var.n[++i]))
                ;

            string power_of_n = var.n.slice(sliceStart, i);
            double n_n = parseNum(power_of_n);

            n = a_n * pow(x, n_n);
        }
        else if (var.n[i] == 's' || var.n[i] == 'c' || var.n[i] == 't') //x^{2sin(2x)}  //trigon
        {
            string tfunc = var.n.slice(i, i + 3);
            string u_n = "";
            int leftPar = 0, rightPar = 0;
            int sliceStart = i + 4; //skip sin(
            leftPar++;

            while (leftPar != rightPar)
            {
                if (var.n == '(')
                    leftPar++;
                if (var.n == ')')
                    rightPar++;

                u_n += var.n[i]; //x^2sin({3x})
                i++;
            }

            double u_value = parseNum(u_n);

            for (unsigned int i = 0; i < u_n.length; i++)
            {
                if (u_n[i] == 'x')
                    u_value *= x;
            }

            if (tfunc == "sin")
                n = a_n * sin(u_value * PI / 180);
            else if (tfunc == "cos")
                n = a_n * cos(u_value * PI / 180);
            else if (tfunc == "tan")
                n = a_n * tan(u_value * PI / 180);
            else if (tfunc == "cot")
                n = a_n / tan(u_value * PI / 180);
            else if (tfunc == "sec")
                n = a_n / cos(u_value * PI / 180);
            else if (tfunc == "csc")
                n = a_n / sin(u_value * PI / 180);
        }
        else if (var.n[i] == 'l')                       //log & ln
        {
            if (term[i + 1] == 'o')     //x^{log10(5x)}
            {
                string u_n = "", b_n = "";
                int leftPar = 0, rightPar = 0;

                while (leftPar != rightPar)
                {
                    if (var.n == '(')
                        leftPar++;
                    if (var.n == ')')
                        rightPar++;
                }
            }
        }

        for (unsigned short i = 0; i < var.u.length; i++)
        {

            if (var.u[i] == 'x')
            {
                //var.u[i] = a_u * x // later-error
            }
        }

        for (unsigned short i = 0; i < term.length; i++)
        {
            if (term[i] == 'x')
            {
                // term[i] = x; // later-error
            }
            else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
            {
                string tfunc = term.slice(i, i + 3);
                if (tfunc == "sin")
                {
                    result = a * sin(parseNum(var.u) * 180 / PI);
                }
                else if (tfunc == "cos")
                {
                    result = a * cos(parseNum(var.u) * 180 / PI);
                }
                else if (tfunc == "tan")
                {
                    result = a * tan(parseNum(var.u) * 180 / PI);
                }
                else if (tfunc == "cot")
                {
                    result = a / tan(parseNum(var.u) * 180 / PI);
                }
                else if (tfunc == "sec")
                {
                    result = a / cos(parseNum(var.u) * 180 / PI);
                }
                else if (tfunc == "csc")
                {
                    result = a / sin(parseNum(var.u) * 180 / PI);
                }
            }
            else if (term[i] == 'l')
            {
                if (term[i + 1] == 'n')
                { //ln
                    ;
                }
                else
                { //log
                    ;
                }
            }
        }
        return result;
    }

    float implCal(string t, float x, float y)
    {
    }

#endif