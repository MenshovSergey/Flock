package parser;

import java.util.Scanner;

public class Parser {

    static String s;
    static double result = 0;

    public double plus(int l, int r) {
        int ans = 0;
              
        boolean check = true;
        for (int i = l; i <= r; i++) {
            if (s.charAt(i) == '+' || s.charAt(i) == '-' || s.charAt(i) == '*' || s.charAt(i) == '/' || s.charAt(i) == '(') {
                check = false;
                break;
            }
        }
        if (check) {
            String s1 = "";
            for (int i = l; i <= r; i++) {
                s1 = s1 + s.charAt(i);
            }
            return Double.parseDouble(s1);
        }
        for (int i = r; l <= i; i--) {
            if (s.charAt(i) == '(') {
                ans++;
            } else {
                if (s.charAt(i) == ')') {
                    ans--;
                } else {
                    if (s.charAt(i) == '-' && ans == 0) {
                        return plus(l, i - 1) - plus(i + 1, r);
                    } else {
                        if (s.charAt(i) == '+' && ans == 0) {
                            return plus(l, i - 1) + plus(i + 1, r);
                        }
                    }
                }
            }
        }
        return mul(l, r);
    }

    public double mul(int l, int r) {
        int ans = 0;
        boolean check = true;

        for (int i = r; l <= i; i--) {
            if (s.charAt(i) == '+' || s.charAt(i) == '-' || s.charAt(i) == '*' || s.charAt(i) == '/' || s.charAt(i) == '(') {
                check = false;
                break;
            }
        }
        if (check) {
            String s1 = "";
            for (int i = l; i <= r; i++) {
                s1 = s1 + s.charAt(i);
            }
            return Double.parseDouble(s1);

        }
        for (int i = r; l <= i; i--) {
            if (s.charAt(i) == ')') {
                ans--;
            } else {
                if (s.charAt(i) == '(') {
                    ans++;
                } else {
                    if (s.charAt(i) == '/' && ans == 0) {
                        return plus(l, i - 1) / plus(i + 1, r);
                    } else {
                        if (s.charAt(i) == '*' && ans == 0) {
                            return plus(l, i - 1) * plus(i + 1, r);
                        }
                    }
                }
            }


        }
        return plus(l + 1, r - 1);

    }

    public String change() {
        String s1 = "";
        for (int i = 0; i < s.length(); i++) {
            if ((s.charAt(i) == '-' || s.charAt(i) == '+') && (i == 0 || s.charAt(i - 1) == '(')) {
                s1 = s1 + '0' + s.charAt(i);
            } else {
                s1 = s1 + s.charAt(i);
            }
        }
        return s1;
    }

    public static void main(String[] args) {
        Scanner t = new Scanner(System.in);
        s = t.nextLine();
        Parser p = new Parser();
        s = p.change();
        System.out.println(p.plus(0, s.length() - 1));


    }
}
