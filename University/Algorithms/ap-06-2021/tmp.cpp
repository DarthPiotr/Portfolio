// jesli odstajacych krawedzi jest za duzo wzgledem podgrafu
/*        if(krawedzie_do_odstajacego*(n-2) > pelny){
            ll zapelnione = (wagi_krawedzi_do_odstajacego - 1)/(n-1);
            wynik += (pelny - krawedzie_do_odstajacego*(n-2)) * zapelnione;
            ll nowe_wagi = wagi_krawedzi_do_odstajacego - (n-2)*zapelnione;
            if(nowe_wagi - 1 >= zapelnione+2){
                ll pozostale = (nowe_wagi-1) - (zapelnione+2) + 1;
                ll zmiana = pozostale*(n-1) - pozostale*(pozostale+1) / 2 - krawedzie_do_odstajacego*pozostale;
                if(zmiana < 0)
                    wynik += zmiana;
            }
        }

        */