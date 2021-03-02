import java.util.*;

/**
 * typeOfSurfaceCurve
 */
public class typeOfSurfaceCurve {

    public static void main(String[] args) {

        double[] coefficients = new double[5];
        String[] ans = new String[2];

        Scanner in = new Scanner(System.in);
        in.useLocale(Locale.ENGLISH);

        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            // zeroing
            coefficients = new double[5];
            ans = new String[2];

            // coefficients reading
            for (int j = 0; j < coefficients.length; j++) {
                coefficients[j] = in.nextDouble();
            }

            // surface
            int rank_e = 0;
            int rank_E = 0;

            for (int j = 0; j < 3; j++) {
                
                if (coefficients[j] != 0) {
                    rank_E++;
                    rank_e++;
                }
            }

            if (coefficients[3] != 0) {
                rank_E++;
            }

            double det = coefficients[0] * coefficients[1] * coefficients[2] * (-coefficients[3]);

            int zero = 0;
            for (int j = 0; j < 3; j++) {
                if (coefficients[j] == 0) {
                    zero++;
                }
            }

            int k = 0;

            int less = 0;
            int more = 0;
            for (int j = 0; j < 3; j++) {
                if (coefficients[j] < 0) {
                    less++;
                } else {
                    if (coefficients[j] > 0) {
                        more++;
                    }
                }
            }

            if (more == 0 || less == 0) {
                k = 1;
            }

            // System.out.println(rank_E);
            // System.out.println(rank_e);
            // System.out.println(k);
            // System.out.println();
            
            if ((less == 0 && coefficients[3] < 0) || (more == 0 && coefficients[3] > 0)) {
                ans[0] = "empty set";
            } else {
                if (coefficients[0] == 1 && coefficients[1] == 1 && coefficients[2] == 1 && coefficients[3] == 0) {
                    ans[0] = "single point";
                } else {
                    if (zero == 2 && coefficients[3] == 0) {
                        ans[0] = "single plane";
                    } else {
                        if (zero == 2) {
                            ans[0] = "pair of parallel planes";
                        } else {
                            if (rank_E == 4 && rank_e == 3 && k == 1) {
                                ans[0] = "ellipsoid";
                            } else {
                                if (rank_E == 3 && rank_e == 3) {
                                    ans[0] = "cone";
                                } else {
                                    if (rank_E == 3 && rank_e == 2 && k == 1) {
                                        ans[0] = "elliptic cylinder";
                                    } else {
                                        if (rank_E == 4 && rank_e == 2 && det < 0) {
                                            ans[0] = "elliptic paraboloid";
                                        } else {
                                            if (rank_E == 3 && rank_e == 2 && k == 0) {
                                                ans[0] = "hyperbolic cylinder";
                                            } else {
                                                if (rank_E == 4 && rank_e == 2 && det > 0) {
                                                    ans[0] = "hyperbolic paraboloid";
                                                } else {
                                                    if (rank_E == 4 && rank_e == 3 && det > 0 && k == 0) {
                                                        ans[0] = "one-sheet hyperboloid";
                                                    } else {
                                                        if (rank_E == 4 && rank_e == 3 && det < 0 && k == 0) {
                                                            ans[0] = "two-sheet hyperboloid";
                                                        } else {
                                                            if (rank_E == 2 && rank_e == 2) {
                                                                ans[0] = "pair of intersecting planes";
                                                            } else {
                                                                if (rank_E == 3 && rank_e == 1) {
                                                                    ans[0] = "parabolic cylinder";
                                                                } else {
                                                                    if (rank_E == 2 && rank_e == 1) {
                                                                        ans[0] = "pair of parallel planes";
                                                                    } else {
                                                                        if (zero == 2 && coefficients[3] == 0) {
                                                                            ans[0] = "single line";
                                                                        } else {
                                                                            ans[0] = "empty set";
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // face
            double det1 = coefficients[1] * (coefficients[0] + coefficients[2]);
            if (det1 == 0) {
                ans[1] = "parabola";
            } else {
                if (det1 > 0) {
                    ans[1] = "ellipse";
                } else {
                    ans[1] = "hyperbola";
                }
            }

            if (ans[0] == "single point" || ans[0] == "pair of parallel planes" || ans[0] == "empty set" || ans[0] == "pair of intersecting planes") {
                ans[1] = ans[0];
            } else {
                if (ans[0] == "single plane") {
                    ans[1] = "single line";
                } else {
                    if (ans[0] == "single line") {
                        ans[1] = "single point";
                    }
                }
            }

            if (coefficients[4] == 0 && ans[0] == "one-sheet hyperboloid") {
                if (coefficients[2] > 0) {
                    ans[1] = "pair of parallel lines";
                } else {
                    ans[1] = "ellipse";
                }
            }

            if (coefficients[4] == 0 && ans[0] == "cone" && coefficients[0] == -1 && coefficients[1] == 1 && coefficients[2] == 1 && coefficients[3] == 0) {
                ans[1] = "single line";
            }
            System.out.println(ans[0] + ", " + ans[1]);
        }
    }
}