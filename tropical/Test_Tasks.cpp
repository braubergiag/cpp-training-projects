// Пример решения из статьи (Комьюетрные инструменты в образовании)
// стр.35 - 41



void Test_Decision_1(){

    MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4);
    A1 << 1,4,2,2,
            d(1,4),1,d(1,3),d(1,4),
            d(1,2),3,1,3,
            d(1,2),4,d(1,3),1;
    A2 << 1,4,2,2,
            d(1,4),1,d(1,3),d(1,4),
            d(1,2),3,1,3,
            d(1,2),4,d(1,3),1;
    A3 << 1,d(1,4),d(1,4),d(1,3),
            4,1,2,2,
            4,d(1,2),1,d(1,3),
            3,d(1,2),3,1;
    A4 << 1,d(1,4),d(1,4),d(1,3),
            4,1,2,2,
            4,d(1,2),1,d(1,3),
            3,d(1,2),3, 1;




    // Шаг 1. Вычисление матрицы Клини
    MaxAlgMatrixXd C_1(4,4);
    std::cout << "Матрица сравнения критериев С:" << std::endl;
    C_1 << 1,4,2,2,
            1./4,1, 1./3, 1./4,
            1./2,3,1,3,
            1./2,4,1./3,1;
    std::cout << C_1 << std::endl;
    double lmb = SpectralRadius(C_1);
    MaxAlgMatrixXd clini_matrix = Clini(d(1,lmb) * C_1) ;

    std::cout << "Cпектральный радиус матрицы С: \u03BB = " << lmb << std::endl;
    std::cout << "[Вычисление] Матрица (1/\u03BB C)* = \n";
    std::cout << clini_matrix << std::endl;
    MaxAlgMatrixXd test_clini_matrix(4,4);
    test_clini_matrix << 1,6,d(2,lmb), d(3*lmb,2),
            d(1,4*lmb),1,d(1,3*lmb),d(lmb,4),
            d(3,4),3*lmb,1,d(3,lmb),
            d(lmb,4),d(4,lmb),d(lmb,3),1;
    std::cout << "[Cтатья] Матрица (1/\u03BB C)* = \n";
    std::cout << test_clini_matrix<< std::endl;

    // Шаг 2.


    FullPivLU<MatrixXd> lu_decomp(clini_matrix.cast<double>());
    MatrixXd P_calc = lu_decomp.image(clini_matrix.cast<double>());


    MaxAlgMatrixXd P(4,2);
    P <<1 ,1,
            d(1,4 * lmb),1/6,
            d(3,4) , d (lmb,2),
            d(lmb,4),d (2,3*lmb);


    std::cout << "[Вычисление] Матрица P = \n";
    std::cout <<  P_calc << std::endl;
    std::cout << "[Cтатья] Матрица P = \n";
    std::cout << P << std::endl;


    VectorXd w_1(4);
    w_1 << 1,d(1,4*lmb), d(3,4), d (lmb,4);
    // Вычесление наихудшего дифф.вектора весов криетериев
    MaxAlgVectorXd Ident(4);
    Ident.setOnes();
    auto det_mat =  (Ident.transpose() * clini_matrix  * Ident).cast<double>();
    double det = det_mat(0);
    //Ident = static_cast<MaxAlgVectorXd>(Ident);
    //auto det = (Ident.transpose() * clini_matrix) * Ident;
    std::cout << det << std::endl;
    MaxAlgMatrixXd V = (d(1,det) * Ident * Ident.transpose()) + (d(1,lmb) * C_1);
    std::cout << "[Вычисление] Матрица V = \n";
    std::cout << V << endl;
    MaxAlgMatrixXd V_test(4,4);
    V_test << d(1,lmb),d(4,lmb),d(2,lmb),d(2,lmb),
            d(1,6),d(1,lmb),d(1,3*lmb),d(1,6),
            d(1,2*lmb),d(3,lmb),d(1,lmb),d(3,lmb),
            d(1,2*lmb),d(4,lmb),d(1,3*lmb),d(1,lmb);
    std::cout << "[Cтатья] Матрица V = \n";
    std::cout << V_test << std::endl;

    // Вычисление матрицы Клини
    MaxAlgMatrixXd V_clini = Clini(V);
    std::cout << "[Вычисление] Матрица Клини V = \n";
    std::cout << V_clini << endl;
    MaxAlgMatrixXd V_clini_test(4,4);
    V_clini_test << 1,6,d(2,lmb),d(3*lmb,2),
            d(1,6),1,d(1,3*lmb),d(lmb,4),
            d(lmb,2),3*lmb,1,d(3,lmb),
            d(2,3*lmb),d(4,lmb),d(lmb,3),1;
    std::cout << "[Статья] Матрица Клини V = \n";
    std::cout << V_clini_test << std::endl;


    FullPivLU<MatrixXd> lu_decomp_2(V_clini.cast<double>());
    MatrixXd w_2 = lu_decomp_2.image(V_clini.cast<double>());
    VectorXd vec(4);
    vec << 1,d(1,6),d(lmb,2),d(2,3*lmb);
    std::cout << "[Статья] Вектор w_2 = " << vec << std::endl;
    std::cout << w_2 * d(1,6) << std::endl;
    // Наилучший дифф. вектор рейтингов альтернатив
    vector<MaxAlgMatrixXd> mat_ = {A1,A2,A3,A4};
    for (auto i = 0; i < w_1.size(); ++i){
        mat_[i] *= w_1(i);
    }

/*    for (auto const & mat : mat_){
        std:: cout << mat << std::endl;
    }*/

    MaxAlgMatrixXd B(4,4);
    B.setIdentity();
    for (auto const & mat : mat_){
        B += mat;
    }
    MatrixXd B_test(4,4);
    B_test << 1,4,2,2,
            3,1,d(3,2),d(3,2),
            3,3,1,3,
            d(9,4),4,d(9,4),1;
    std::cout << "[Вычисление] Матрица B = \n" << B << std::endl;
    std::cout << "[Статья] Матрица B = \n" << B_test << std::endl;

    double mu = SpectralRadius(B);
    std::cout << "[Вычисление] Спектральный радиус B = " << mu << std::endl;
    MaxAlgMatrixXd B_clini = Clini(d(1,mu) * B);
    std::cout << "[Вычисление] Матрциа Клини (mu^-1 B)* = \n";
    std::cout << B_clini << std::endl;

    MaxAlgMatrixXd clini_B_test(4,4);
    clini_B_test << 1,d(mu,3),d(mu,6),d(mu,6),
            d(mu,4),1,d(1,2),d(1,2),
            d(mu,4),1,1,d(mu,4),
            1,d(mu,3),d(3*mu,16),1;
    std::cout << "[Статья] Матрциа Клини (mu^-1 B)* = \n";
    std::cout << clini_B_test << std::endl;



    FullPivLU<MatrixXd> lu_decomp_3(B_clini.cast<double>());
    MatrixXd Q = lu_decomp_3.image(B_clini.cast<double>());
    std::cout << "[Вычисление] Q = \n";
    std::cout << Q << std::endl;
    MatrixXd Q_test(4,3);
    Q_test << 1,d(mu,6),d(mu,6),
            d(mu,4),d(1,2),d(1,2),
            d(mu,4),1,d(mu,4),
            1,d(3*mu,16),1;

    std::cout << "[Статья] Q = \n";
    std::cout << Q_test << std::endl;
}

void Test_Decision_2(){
    MaxAlgMatrixXd C(2,2), A1(3,3),A2(3,3);
    C << 1,d(1,3),
            3,1;
    A1 << 1,3,d(1,3),
            d(1,3),1,1,
            3,1,1;
    A2 << 1,d(1,3),5,
            3,1,7,
            d(1,5),d(1,7),1;

    double lamb = SpectralRadius(C);
    Vector2d w(1,3);
    vector<MaxAlgMatrixXd> mat_ = {A1,A2};
    for (auto i = 0; i < w.size(); ++i){
        mat_[i] *= w(i);
    }
/*    for (auto const & mat : mat_){
        std:: cout << mat << std::endl;
    }*/

    MaxAlgMatrixXd res(3,3);
    res.setIdentity();
    for (auto const & mat : mat_){
        res += mat;
    }
    double res_lamb = SpectralRadius(res);
    //std::cout << res_lamb;
    auto clini_matrix= Clini(d(1,res_lamb) * res);
    FullPivLU<MatrixXd> lu_decomp(clini_matrix.cast<double>());
    std::cout << lu_decomp.image(clini_matrix.cast<double>());





}

void Test_New_Decision() {
    /* Матрицы сравнения альтернатив*/

    MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4);
    A1 << 1,4,2,2,
            d(1,4),1,d(1,3),d(1,4),
            d(1,2),3,1,3,
            d(1,2),4,d(1,3),1;
    A2 << 1,4,2,2,
            d(1,4),1,d(1,3),d(1,4),
            d(1,2),3,1,3,
            d(1,2),4,d(1,3),1;
    A3 << 1,d(1,4),d(1,4),d(1,3),
            4,1,2,2,
            4,d(1,2),1,d(1,3),
            3,d(1,2),3,1;
    A4 << 1,d(1,4),d(1,4),d(1,3),
            4,1,2,2,
            4,d(1,2),1,d(1,3),
            3,d(1,2),3, 1;




    std::cout << "4.1. Результаты решения задачи 1\n";
    /* 1
     * Определение для заданной матрицы C парных сравнений K кри-
териев наилучшего и наихудшего векторов весов*/
    std::cout << "1.\n" <<
              "Определение для заданной матрицы C парных сравнений K кри-\n" <<
              "териев наилучшего и наихудшего векторов весов\n";
    MaxAlgMatrixXd C(4, 4);
    std::cout << "Матрица сравнения критериев С:" << std::endl;
    C << 1, 4, 2, 2,
            1. / 4, 1, 1. / 3, 1. / 4,
            1. / 2, 3, 1, 3,
            1. / 2, 4, 1. / 3, 1;

    std::cout << C << std::endl;
    // 1.1. Построение генерирующей матрицы оптимальных весов
    std::cout << "1.1. Построение генерирующей матрицы оптимальных весов\n";
    double lmb = SpectralRadius(C);
    MaxAlgMatrixXd D = Clini(d(1, lmb) * C);
    std::cout << "D = \n" << D << std::endl;

    /* 1.2 Вычисление по матрице D со столбцами d_1 , . . . , d_K
     * наилучшего дифференцирующего вектора весов
     */
    std::cout << "1.2. Вычисление по матрице D со столбцами d_1 , . . . , d_K\n" <<
              " наилучшего дифференцирующего вектора весов\n";
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int l_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            l_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс l = " << l_ << std::endl;
    MaxAlgMatrixXd v = D.col(l_) * d(1,static_cast<double>(D.col(l_).sum()));
    Vector4d v_test = {1,d(1,4*lmb),d(3,4),d(lmb,4)};
    std::cout << "[Вычисление] v = \n" << v << std::endl;
    std::cout << "[Статья] v  = \n" << v_test << std::endl;;

/* 1.3
 * Вычисление по матрице D наихудшего дифференцирующего вектора весов
 * */
    std::cout << "1.3." <<
              " Вычисление по матрице D наихудшего дифференцирующего вектора весов\n";

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
    Vector4d w_test = {1,d(1,6),d(lmb,2),d(2,3*lmb)};
    std::cout << "[Вычисление] w = " << w.cast<double>() << std::endl;
    std::cout << "[Статья] w  = " <<w_test << std::endl;;

    /* 2
     * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-
    ференцирующего вектора рейтингов альтернатив.
     * */
    std::cout << "2\n"
                 " Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              " N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-\n" <<
              " ференцирующего вектора рейтингов альтернатив.\n";


    /* 2.1
     * Вычисление взвешенной суммы матриц парных сравнений
     * */
    std::cout << "2.1" <<
              " Вычисление взвешенной суммы матриц парных сравнений";

    vector<MaxAlgMatrixXd> mat_ = {A1,A2,A3,A4};
    for (auto i = 0; i < v.size(); ++i){
        mat_[i] *= v(i);
    }
    MaxAlgMatrixXd P(A1.rows(),A1.cols());
    P.setIdentity();
    for (auto const & mat : mat_){
        P += mat;
    }
    MatrixXd P_test(4, 4);
    P_test << 1,4,2,2,
            3,1,d(3,2),d(3,2),
            3,3,1,3,
            d(9,4),4,d(9,4),1;
    std::cout << "[Вычисление] Матрица P = \n" << P << std::endl;
    std::cout << "[Статья] Матрица P = \n" << P_test << std::endl;

    /* 2.2
     * Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "2.2." <<
              " Построение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double mu = SpectralRadius(P);
    std::cout << "[Вычисление] Спектральный радиус P = " << mu << std::endl;
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P);
    std::cout << "[Вычисление] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;

    MaxAlgMatrixXd Q_test(4,4);
    Q_test << 1,d(mu,3),d(mu,6),d(mu,6),
            d(mu,4),1,d(1,2),d(1,2),
            d(mu,4),1,1,d(mu,4),
            1,d(mu,3),d(3*mu,16),1;
    std::cout << "[Статья] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q_test << std::endl;

    /* 2.3
     * Вычисление по матрице Q со столбцами q 1 , . . . , q N наилучшего
     * дифференцирующего вектора рейтингов альтернатив
     * */

    std::cout << " 2.3\n"
                 "  Вычисление по матрице Q со столбцами q_1 , . . . , q_N наилучшего\n" <<
              "  дифференцирующего вектора рейтингов альтернат\n";
    I.resize(Q.rows());
    I.setOnes();
    current_max = 0;
    int m_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            m_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(l_).sum()));
    Vector4d X_test_1 = {d(mu,6),d(1,2),1,d(3*mu,16)};
    Vector4d X_test_2 = {d(mu,6),d(1,2),d(mu,4),1};
    std::cout << "[Вычисление] наилучшего дифференцирующего вектора рейтингов альтернатив\n";
    std::cout << "[Вычисление] x = \n" << X << std::endl;
    std::cout << "[Статья] x_1 = \n" << X_test_1 << std::endl;;
    std::cout << "[Статья] x_2  = \n" << X_test_2 << std::endl;;


/* 3
 * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов w = (w_1 , . . . , w_K ) T наихудшего
    дифференцирующего вектора рейтингов альтернатив
 *
 * */
    std::cout << "3.\n" <<
              "Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              "N альтернатив и вектора весов w = (w_1 , . . . , w_K )^T наихудшего\n" <<
              "дифференцирующего вектора рейтингов альтернатив";

/* 3.1
 * Вычисление взвешенной суммы матриц парных сравнений
 * */
    std::cout << "3.1\n"
                 " * Вычисление взвешенной суммы матриц парных сравнений\n";
    vector<MaxAlgMatrixXd> mat_R = {A1,A2,A3,A4};
    for (auto i = 0; i < w.size(); ++i){
        mat_R[i] *= w(i);
    }
    MaxAlgMatrixXd R(A1.rows(),A1.cols());
    R.setIdentity();
    for (auto const & mat : mat_R){
        R += mat;
    }
    MatrixXd R_test(4, 4);
    R_test << 1,4,2,2,
            2*lmb,1,lmb,lmb,
            2*lmb,3,1,3,
            d(3*lmb,2),4,d(3*lmb,2),1;
    std::cout << "[Вычисление] Матрица R = \n" << R << std::endl;
    std::cout << "[Статья] Матрица R = \n" << R_test << std::endl;


    /* 3.2
     *Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "3.2\nПостроение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double vu = SpectralRadius(R);
    std::cout << "[Вычисление] Спектральный радиус матрицы R = " << vu << std::endl;
    MaxAlgMatrixXd S = Clini(d(1, vu) * R);
    std::cout << "[Вычисление] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S << std::endl;
    MaxAlgMatrixXd S_test(4,4);

    S_test << 1,d(4,vu),d(2,vu),d(2,vu),
            d(vu,4),1,d(1,2),d(1,2),
            d(vu,4),1,1,d(3,vu),
            1,d(4,vu),d(3*vu,16),1;

    std::cout << "[Статья] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S_test << std::endl;


/* 3.3
 * Вычисление по матрице S наихудшего дифференцирующего вектора рейтингов альтернатив
 * */
    std::cout << "3.3\nВычисление по матрице S наихудшего дифференцирующего\n" <<
              "вектора рейтингов альтернатив\n";
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    std::cout << "[Вычисление] y = \n" << y << std::endl;
    Vector4d y_test_1 = {1,d(vu,4),d(vu,4),1};
    Vector4d y_test_2 = {1,d(vu,4),1,1};
    std::cout << "[Статья] y_1 = \n" << y_test_1 << std::endl;;
    std::cout << "[Статья] y_2  = \n" << y_test_2 << std::endl;;


    std::cout << "------------------Результаты---------------\n";
    std::cout << "Наилучший вектор рейтингов альтернатив: x =\n" <<  X << std::endl;
    std::cout << "Наихудший вектор рейтингов альтернатив: y =\n" << y.cast<double>() << std::endl;


}
void Test_New_Decision_2(){

    MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4);
    A1 << 1,2,2,4,
            d(1,2),1,3,3,
            d(1,2),d(1,3),1,4,
            d(1,4),d(1,3),d(1,4),1;
    A2 << 1,d(1,4),d(1,3),d(1,4),
            4,1,4,d(1,2),
            3,d(1,4),1,d(1,2),
            4,2,2,1;
    A3 << 1,d(1,4),d(1,3),d(1,4),
            4,1,4,d(1,2),
            3,d(1,4),1,d(1,2),
            4,2,2, 1;
    A4 << 1,2,2,4,
            d(1,2),1,3,3,
            d(1,2),d(1,3),1,4,
            d(1,4),d(1,3),d(1,4),1;





    std::cout << "4.2. Результаты решения задачи 2\n";
    /* 1
     * Определение для заданной матрицы C парных сравнений K кри-
териев наилучшего и наихудшего векторов весов*/
    std::cout << "1.\n" <<
              "Определение для заданной матрицы C парных сравнений K кри-\n" <<
              "териев наилучшего и наихудшего векторов весов\n";
    MaxAlgMatrixXd C(4, 4);
    std::cout << "Матрица сравнения критериев С:" << std::endl;
    C << 1, 2, 2, 4,
            d(1,2), 1, 3, 3,
            d(1,2), d(1,3), 1, 4,
            d(1,4), d(1,3), d(1,4), 1;

    std::cout << C << std::endl;
    // 1.1. Построение генерирующей матрицы оптимальных весов
    std::cout << "1.1. Построение генерирующей матрицы оптимальных весов\n";
    double lmb = SpectralRadius(C);
    MaxAlgMatrixXd D = Clini(d(1, lmb) * C);
    std::cout << "D = \n" << D << std::endl;

    /* 1.2 Вычисление по матрице D со столбцами d_1 , . . . , d_K
 * наилучшего дифференцирующего вектора весов
 */
    std::cout << "1.2. Вычисление по матрице D со столбцами d_1 , . . . , d_K\n" <<
              " наилучшего дифференцирующего вектора весов\n";
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int l_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            l_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс l = " << l_ << std::endl;
    MaxAlgMatrixXd v = D.col(l_) * d(1,static_cast<double>(D.col(l_).sum()));
    Vector4d v_test = {1,d(3,4),d(lmb,4),d(1,4*lmb)};
    std::cout << "[Вычисление] v = \n" << v << std::endl;
    std::cout << "[Статья] v  = \n" << v_test << std::endl;;

/* 1.3
 * Вычисление по матрице D наихудшего дифференцирующего вектора весов
 * */
    std::cout << "1.3." <<
              " Вычисление по матрице D наихудшего дифференцирующего вектора весов\n";

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
    Vector4d w_test = {1,d(lmb,2),d(2,3*lmb),d(1,6)};
    std::cout << "[Вычисление] w = " << w.cast<double>() << std::endl;
    std::cout << "[Статья] w  = " <<w_test << std::endl;;

    /* 2
     * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-
    ференцирующего вектора рейтингов альтернатив.
     * */
    std::cout << "2\n"
                 " Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              " N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-\n" <<
              " ференцирующего вектора рейтингов альтернатив.\n";


    /* 2.1
     * Вычисление взвешенной суммы матриц парных сравнений
     * */
    std::cout << "2.1" <<
              " Вычисление взвешенной суммы матриц парных сравнений";

    vector<MaxAlgMatrixXd> mat_ = {A1,A2,A3,A4};
    for (auto i = 0; i < v.size(); ++i){
        mat_[i] *= v(i);
    }
    MaxAlgMatrixXd P(A1.rows(),A1.cols());
    P.setIdentity();
    for (auto const & mat : mat_){
        P += mat;
    }
    MatrixXd P_test(4, 4);
    P_test << 1,2,2,4,
            3,1,3,3,
            d(9,4),d(1,3),1,4,
            3,d(3,2),d(3,2),1;
    std::cout << "[Вычисление] Матрица P = \n" << P << std::endl;
    std::cout << "[Статья] Матрица P = \n" << P_test << std::endl;

    /* 2.2
     * Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "2.2." <<
              " Построение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double mu = SpectralRadius(P);
    std::cout << "[Вычисление] Спектральный радиус P = " << mu << std::endl;
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P);
    std::cout << "[Вычисление] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;

    MaxAlgMatrixXd Q_test(4,4);
    Q_test << 1,d(mu,6),d(mu,6),d(mu,3),
            d(mu,4),1,d(mu,4),1,
            1,d(mu,6),1,d(mu,3),
            d(mu,4),d(1,2),d(1,2),1;
    std::cout << "[Статья] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q_test << std::endl;

    /* 2.3
     * Вычисление по матрице Q со столбцами q 1 , . . . , q N наилучшего
     * дифференцирующего вектора рейтингов альтернатив
     * */

    std::cout << " 2.3\n"
                 "  Вычисление по матрице Q со столбцами q_1 , . . . , q_N наилучшего\n" <<
              "  дифференцирующего вектора рейтингов альтернат\n";
    I.resize(Q.rows());
    I.setOnes();
    current_max = 0;
    int m_ = 0;
    for (auto i = 0; i < Q.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            m_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(l_).sum()));
    Vector4d X_test_1 = {d(mu,6),1,d(mu,6),d(1,2)};
    Vector4d X_test_2 = {d(mu,6),d(mu,4),1,d(1,2)};
    std::cout << "[Вычисление] наилучшего дифференцирующего вектора рейтингов альтернатив\n";
    std::cout << "[Вычисление] x = \n" << X << std::endl;
    std::cout << "[Статья] x_1 = \n" << X_test_1 << std::endl;;
    std::cout << "[Статья] x_2  = \n" << X_test_2 << std::endl;;


/* 3
 * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов w = (w_1 , . . . , w_K ) T наихудшего
    дифференцирующего вектора рейтингов альтернатив
 *
 * */
    std::cout << "3.\n" <<
              "Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              "N альтернатив и вектора весов w = (w_1 , . . . , w_K )^T наихудшего\n" <<
              "дифференцирующего вектора рейтингов альтернатив";

/* 3.1
 * Вычисление взвешенной суммы матриц парных сравнений
 * */
    std::cout << "3.1\n"
                 " * Вычисление взвешенной суммы матриц парных сравнений\n";
    vector<MaxAlgMatrixXd> mat_R = {A1,A2,A3,A4};
    for (auto i = 0; i < w.size(); ++i){
        mat_R[i] *= w(i);
    }
    MaxAlgMatrixXd R(A1.rows(),A1.cols());
    R.setIdentity();
    for (auto const & mat : mat_R){
        R += mat;
    }
    MatrixXd R_test(4, 4);
    R_test << 1,2,2,4,
            2*lmb,1,2*lmb,3,
            d(3*lmb,2),d(1,3),1,4,
            2*lmb,lmb,lmb,1;
    std::cout << "[Вычисление] Матрица R = \n" << R << std::endl;
    std::cout << "[Статья] Матрица R = \n" << R_test << std::endl;


    /* 3.2
     *Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "3.2\nПостроение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double vu = SpectralRadius(R);
    std::cout << "[Вычисление] Спектральный радиус матрицы R = " << vu << std::endl;
    MaxAlgMatrixXd S = Clini(d(1, vu) * R);
    std::cout << "[Вычисление] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S << std::endl;
    MaxAlgMatrixXd S_test(4,4);

    S_test << 1,1,1,d(4,vu),
            d(vu,4),1,d(vu,4),1,
            1,1,1,d(4,vu),
            d(vu,4),d(4,vu),d(vu,4),1;

    std::cout << "[Статья] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S_test << std::endl;


/* 3.3
 * Вычисление по матрице S наихудшего дифференцирующего вектора рейтингов альтернатив
 * */
    std::cout << "3.3\nВычисление по матрице S наихудшего дифференцирующего\n" <<
              "вектора рейтингов альтернатив\n";
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    std::cout << "[Вычисление] y = \n" << y << std::endl;
    Vector4d y_test_1 = {1,d(vu,4),1,d(vu,4)};
    Vector4d y_test_2 = {1,1,1,d(vu,4)};
    std::cout << "[Статья] y_1 = \n" << y_test_1 << std::endl;;
    std::cout << "[Статья] y_2  = \n" << y_test_2<< std::endl;;
    std::cout << "------------------Результаты---------------\n";
    std::cout << "Наилучший вектор рейтингов альтернатив: x =\n" <<  X << std::endl;
    std::cout << "Наихудший вектор рейтингов альтернатив: y =\n" << y.cast<double>() << std::endl;

}
void Test_New_Descision_3(){
    std::cout << "5.1. Решение задачи о выборе места работы";
    MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

    A1 << 1,d(1,4),d(1,2),
            4,1,3,
            2,d(1,3),1;
    A2 << 1,d(1,4),d(1,5),
            4,1,d(1,2),
            5,2,1;
    A3 << 1,3,d(1,3),
            d(1,3),1,1,
            3,1,1;
    A4 << 1,d(1,3),5,
            3,1,7,
            d(1,5),d(1,7),1;
    A5 << 1,1,7,
            1,1,7,
            d(1,7),d(1,7),1;
    A6 << 1,7,9,
            d(1,7),1,5,
            d(1,9),d(1,5),1;

    std::cout << "1.\n" <<
              "Определение для заданной матрицы C парных сравнений K кри-\n" <<
              "териев наилучшего и наихудшего векторов весов\n";
    MaxAlgMatrixXd C(6, 6);
    std::cout << "Матрица сравнения критериев С:" << std::endl;
    C << 1, 1,1,4,1,d(1,2),
            1,1,2,4,1,d(1,2),
            1,d(1,2),1,5,3,d(1,2),
            d(1,4),d(1,4),d(1,5),1,d(1,3),d(1,3),
            1,1,d(1,3),3,1,1,
            2,2,2,3,1,1;
    std::cout << C << std::endl;
    // 1.1. Построение генерирующей матрицы оптимальных весов
    std::cout << "1.1. Построение генерирующей матрицы оптимальных весов\n";
    double lmb = SpectralRadius(C);
    MaxAlgMatrixXd D = Clini(d(1, lmb) * C);
    std::cout << "D = \n" << D << std::endl;

    /* 1.2 Вычисление по матрице D со столбцами d_1 , . . . , d_K
 * наилучшего дифференцирующего вектора весов
 */
    std::cout << "1.2. Вычисление по матрице D со столбцами d_1 , . . . , d_K\n" <<
              " наилучшего дифференцирующего вектора весов\n";
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int l_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            l_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс l = " << l_ << std::endl;
    MaxAlgMatrixXd v = D.col(l_) * d(1,static_cast<double>(D.col(l_).sum()));
//    Vector4d v_test = {1,d(3,4),d(lmb,4),d(1,4*lmb)};
    std::cout << "[Вычисление] v = \n" << v << std::endl;
//    std::cout << "[Статья] v  = \n" << v_test << std::endl;;

/* 1.3
 * Вычисление по матрице D наихудшего дифференцирующего вектора весов
 * */
    std::cout << "1.3." <<
              " Вычисление по матрице D наихудшего дифференцирующего вектора весов\n";

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
//    Vector4d w_test = {1,d(lmb,2),d(2,3*lmb),d(1,6)};
    std::cout << "[Вычисление] w = " << w.transpose().cast<double>() << std::endl;
//    std::cout << "[Статья] w  = " <<w_test.transpose() << std::endl;;

    /* 2
     * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-
    ференцирующего вектора рейтингов альтернатив.
     * */
    std::cout << "2\n"
                 " Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              " N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-\n" <<
              " ференцирующего вектора рейтингов альтернатив.\n";


    /* 2.1
     * Вычисление взвешенной суммы матриц парных сравнений
     * */
    std::cout << "2.1" <<
              " Вычисление взвешенной суммы матриц парных сравнений";

    vector<MaxAlgMatrixXd> mat_ = {A1,A2,A3,A4,A5,A6};
    for (auto i = 0; i < v.size(); ++i){
        mat_[i] *= v(i);
    }
    MaxAlgMatrixXd P(A1.rows(),A1.cols());
    P.setIdentity();
    for (auto const & mat : mat_){
        P += mat;
    }
    /*MatrixXd P_test(4, 4);
    P_test << 1,2,2,4,
            3,1,3,3,
            d(9,4),d(1,3),1,4,
            3,d(3,2),d(3,2),1;*/
    std::cout << "[Вычисление] Матрица P = \n" << P << std::endl;
//    std::cout << "[Статья] Матрица P = \n" << P_test << std::endl;

    /* 2.2
     * Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "2.2." <<
              " Построение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double mu = SpectralRadius(P);
    std::cout << "[Вычисление] Спектральный радиус P = " << mu << std::endl;
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P);
    std::cout << "[Вычисление] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;

    /* MaxAlgMatrixXd Q_test(4,4);
     Q_test << 1,d(mu,6),d(mu,6),d(mu,3),
             d(mu,4),1,d(mu,4),1,
             1,d(mu,6),1,d(mu,3),
             d(mu,4),d(1,2),d(1,2),1;
     std::cout << "[Статья] Матрциа Клини Q = (mu^-1 P)* = \n";
     std::cout << Q_test << std::endl;*/

    /* 2.3
     * Вычисление по матрице Q со столбцами q 1 , . . . , q N наилучшего
     * дифференцирующего вектора рейтингов альтернатив
     * */

    std::cout << " 2.3\n"
                 "  Вычисление по матрице Q со столбцами q_1 , . . . , q_N наилучшего\n" <<
              "  дифференцирующего вектора рейтингов альтернат\n";
    I.resize(Q.rows());
    I.setOnes();
    current_max = 0;
    int m_ = 0;
    for (auto i = 0; i < Q.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            m_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(l_).sum()));
    Vector3d X_test_1 = {1,d(2*lmb,mu),d(mu,9)};
//    Vector4d X_test_2 = {d(mu,6),d(mu,4),1,d(1,2)};
    std::cout << "[Вычисление] наилучшего дифференцирующего вектора рейтингов альтернатив\n";
    std::cout << "[Вычисление] x = \n" << X << std::endl;
    std::cout << "[Статья] x_1 = \n" << X_test_1 << std::endl;;
//    std::cout << "[Статья] x_2  = \n" << X_test_2.transpose() << std::endl;;


/* 3
 * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов w = (w_1 , . . . , w_K ) T наихудшего
    дифференцирующего вектора рейтингов альтернатив
 *
 * */
    std::cout << "3.\n" <<
              "Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              "N альтернатив и вектора весов w = (w_1 , . . . , w_K )^T наихудшего\n" <<
              "дифференцирующего вектора рейтингов альтернатив";

/* 3.1
 * Вычисление взвешенной суммы матриц парных сравнений
 * */
    std::cout << "3.1\n"
                 " * Вычисление взвешенной суммы матриц парных сравнений\n";
    vector<MaxAlgMatrixXd> mat_R = {A1,A2,A3,A4,A5,A6};
    for (auto i = 0; i < w.size(); ++i){
        mat_R[i] *= w(i);
    }
    MaxAlgMatrixXd R(A1.rows(),A1.cols());
    R.setIdentity();
    for (auto const & mat : mat_R){
        R += mat;
    }

    std::cout << "[Вычисление] Матрица R = \n" << R << std::endl;



    /* 3.2
     *Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "3.2\nПостроение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double vu = SpectralRadius(R);
    std::cout << "[Вычисление] Спектральный радиус матрицы R = " << vu << std::endl;
    MaxAlgMatrixXd S = Clini(d(1, vu) * R);
    std::cout << "[Вычисление] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S << std::endl;



/* 3.3
 * Вычисление по матрице S наихудшего дифференцирующего вектора рейтингов альтернатив
 * */
    std::cout << "3.3\nВычисление по матрице S наихудшего дифференцирующего\n" <<
              "вектора рейтингов альтернатив\n";
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    std::cout << "[Вычисление] y = \n" << y << std::endl;
    Vector3d y_test_1 = {1,d(vu,9),d(vu,9)};
    Vector3d y_test_2 = {1,d(vu,7),d(vu,9)};
    std::cout << "[Статья] y_1 = \n" << y_test_1 << std::endl;;
    std::cout << "[Статья] y_2  = \n" << y_test_2 << std::endl;;

    std::cout << "------------------Результаты---------------\n";
    std::cout << "Наилучший вектор рейтингов альтернатив: x =\n" <<  X << std::endl;
    std::cout << "Наихудший вектор рейтингов альтернатив: y =\n" << y.cast<double>() << std::endl;


}
void Test_New_Decision_4(){
    std::cout << "5.2. Решение задачи о выборе места жительства";
    MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4),A5(4,4);
    A1 << 1,d(1,2),1,d(1,2),
            2,1,d(5,2),1,
            1,d(2,5),1,d(2,5),
            2,1,d(5,2),1;
    A2 << 1,2,d(1,3),4,
            d(1,2),1,d(1,8),2,
            3,8,1,9,
            d(1,4),d(1,2),d(1,9),1;
    A3 << 1,5,d(1,2),d(5,2),
            d(1,5),1,d(1,9),d(1,4),
            2,9,1,7,
            d(2,5),4,d(1,7),1;
    A4 << 1,d(1,2),3,4,
            2,1,6,8,
            d(1,3),d(1,6),1,1,
            d(1,4),d(1,8),1,1;
    A5 << 1,d(3,2),d(1,2),4,
            d(2,3),1,d(2,7),d(5,2),
            2,d(7,2),1,9,
            d(1,4),d(2,5),d(1,9),1;






    std::cout << "1.\n" <<
              "Определение для заданной матрицы C парных сравнений K кри-\n" <<
              "териев наилучшего и наихудшего векторов весов\n";
    MaxAlgMatrixXd C(5, 5);
    std::cout << "Матрица сравнения критериев С:" << std::endl;
    C << 1,d(1,5),3,d(1,2),5,
            5,1,7,1,7,
            d(1,3),d(1,7),1,d(1,4),3,
            2,1,4,1,7,
            d(1,5),d(1,7),d(1,3),d(1,7),1;
    std::cout << C << std::endl;
    // 1.1. Построение генерирующей матрицы оптимальных весов
    std::cout << "1.1. Построение генерирующей матрицы оптимальных весов\n";
    double lmb = SpectralRadius(C);
    std::cout << "Cпектральный радиус матрицы С = " << lmb << std::endl;
    MaxAlgMatrixXd D = Clini(d(1, lmb) * C);
    std::cout << "D = \n" << D << std::endl;

    /* 1.2 Вычисление по матрице D со столбцами d_1 , . . . , d_K
 * наилучшего дифференцирующего вектора весов
 */
    std::cout << "1.2. Вычисление по матрице D со столбцами d_1 , . . . , d_K\n" <<
              " наилучшего дифференцирующего вектора весов\n";
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int l_ = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            l_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс l = " << l_ << std::endl;
    MaxAlgMatrixXd v = D.col(l_) * d(1,static_cast<double>(D.col(l_).sum()));
//    Vector4d v_test = {1,d(3,4),d(lmb,4),d(1,4*lmb)};
    std::cout << "[Вычисление] v = \n" << v << std::endl;
//    std::cout << "[Статья] v  = \n" << v_test << std::endl;;

/* 1.3
 * Вычисление по матрице D наихудшего дифференцирующего вектора весов
 * */
    std::cout << "1.3." <<
              " Вычисление по матрице D наихудшего дифференцирующего вектора весов\n";

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
//    Vector4d w_test = {1,d(lmb,2),d(2,3*lmb),d(1,6)};
    std::cout << "[Вычисление] w = " << w.cast<double>() << std::endl;
//    std::cout << "[Статья] w  = " <<w_test.transpose() << std::endl;;

    /* 2
     * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-
    ференцирующего вектора рейтингов альтернатив.
     * */
    std::cout << "2\n"
                 " Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              " N альтернатив и вектора весов v = (v_1 , . . . , v_K )^T наилучшего диф-\n" <<
              " ференцирующего вектора рейтингов альтернатив.\n";


    /* 2.1
     * Вычисление взвешенной суммы матриц парных сравнений
     * */
    std::cout << "2.1" <<
              " Вычисление взвешенной суммы матриц парных сравнений";

    vector<MaxAlgMatrixXd> mat_ = {A1,A2,A3,A4,A5};
    for (auto i = 0; i < v.size(); ++i){
        mat_[i] *= v(i);
    }
    MaxAlgMatrixXd P(A1.rows(),A1.cols());
    P.setIdentity();
    for (auto const & mat : mat_){
        P += mat;
    }
    /*MatrixXd P_test(4, 4);
    P_test << 1,2,2,4,
            3,1,3,3,
            d(9,4),d(1,3),1,4,
            3,d(3,2),d(3,2),1;*/
    std::cout << "[Вычисление] Матрица P = \n" << P << std::endl;
//    std::cout << "[Статья] Матрица P = \n" << P_test << std::endl;

    /* 2.2
     * Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "2.2." <<
              " Построение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double mu = SpectralRadius(P);
    std::cout << "[Вычисление] Спектральный радиус P = " << mu << std::endl;
    MaxAlgMatrixXd Q = Clini(d(1,mu) * P);
    std::cout << "[Вычисление] Матрциа Клини Q = (mu^-1 P)* = \n";
    std::cout << Q << std::endl;

    /* MaxAlgMatrixXd Q_test(4,4);
     Q_test << 1,d(mu,6),d(mu,6),d(mu,3),
             d(mu,4),1,d(mu,4),1,
             1,d(mu,6),1,d(mu,3),
             d(mu,4),d(1,2),d(1,2),1;
     std::cout << "[Статья] Матрциа Клини Q = (mu^-1 P)* = \n";
     std::cout << Q_test << std::endl;*/

    /* 2.3
     * Вычисление по матрице Q со столбцами q 1 , . . . , q N наилучшего
     * дифференцирующего вектора рейтингов альтернатив
     * */

    std::cout << " 2.3\n"
                 "  Вычисление по матрице Q со столбцами q_1 , . . . , q_N наилучшего\n" <<
              "  дифференцирующего вектора рейтингов альтернат\n";
    I.resize(Q.rows());
    I.setOnes();
    current_max = 0;
    int m_ = 0;
    for (auto i = 0; i < Q.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            m_ =  i;
            current_max = r1(0).scalar;
        }

    }
    std::cout << " Индекс m = " << m_ << std::endl;
    MaxAlgMatrixXd X = Q.col(m_) * d(1,static_cast<double>(Q.col(l_).sum()));
//    Vector3d X_test_1 = {1,d(2*lmb,mu),d(mu,9)};
//    Vector4d X_test_2 = {d(mu,6),d(mu,4),1,d(1,2)};
    std::cout << "[Здесь вектор отличается в одой из позиций (стр.50) \n";
    std::cout << "[Вычисление] наилучшего дифференцирующего вектора рейтингов альтернатив\n";
    std::cout << "[Вычисление] x = \n" << X << std::endl;
//    std::cout << "[Статья] x_1 = \n" << X_test_1.transpose() << std::endl;;
//    std::cout << "[Статья] x_2  = \n" << X_test_2.transpose() << std::endl;;


/* 3
 * Определение для заданных матриц A_1 , . . . , A_K парных сравнений
    N альтернатив и вектора весов w = (w_1 , . . . , w_K ) T наихудшего
    дифференцирующего вектора рейтингов альтернатив
 *
 * */
    std::cout << "3.\n" <<
              "Определение для заданных матриц A_1 , . . . , A_K парных сравнений\n" <<
              "N альтернатив и вектора весов w = (w_1 , . . . , w_K )^T наихудшего\n" <<
              "дифференцирующего вектора рейтингов альтернатив";

/* 3.1
 * Вычисление взвешенной суммы матриц парных сравнений
 * */
    std::cout << "3.1\n"
                 " * Вычисление взвешенной суммы матриц парных сравнений\n";
    vector<MaxAlgMatrixXd> mat_R = {A1,A2,A3,A4,A5};
    for (auto i = 0; i < w.size(); ++i){
        mat_R[i] *= w(i);
    }
    MaxAlgMatrixXd R(A1.rows(),A1.cols());
    R.setIdentity();
    for (auto const & mat : mat_R){
        R += mat;
    }

    std::cout << "[Вычисление] Матрица R = \n" << R << std::endl;



    /* 3.2
     *Построение генерирующей матрицы оптимальных рейтингов альтернатив
     * */

    std::cout << "3.2\nПостроение генерирующей матрицы оптимальных рейтингов альтернатив\n";
    double vu = SpectralRadius(R,"R");
    std::cout << "[Вычисление] Спектральный радиус матрицы R = " << vu << std::endl;
    MaxAlgMatrixXd S = Clini(d(1, vu) * R);
    std::cout << "[Вычисление] Матрциа Клини S = (v^-1 R)* = \n";
    std::cout << S << std::endl;



/* 3.3
 * Вычисление по матрице S наихудшего дифференцирующего вектора рейтингов альтернатив
 * */
    std::cout << "3.3\nВычисление по матрице S наихудшего дифференцирующего\n" <<
              "вектора рейтингов альтернатив\n";
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    std::cout << "[Вычисление] y = \n" << y << std::endl;
//    Vector3d y_test_1 = {1,d(vu,9),d(vu,9)};
//    Vector3d y_test_2 = {1,d(vu,7),d(vu,9)};
//    std::cout << "[Статья] y_1 = \n" << y_test_1.transpose() << std::endl;;
//    std::cout << "[Статья] y_2  = \n" << y_test_2.transpose() << std::endl;;
    std::cout << "------------------Результаты---------------\n";
    std::cout << "Наилучший вектор рейтингов альтернатив: x =\n" <<  X << std::endl;
    std::cout << "Наихудший вектор рейтингов альтернатив: y =\n" << y.cast<double>() << std::endl;
}


