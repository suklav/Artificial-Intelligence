(set-logic QF_LIA)


(declare-fun Q11 () Int)
(declare-fun Q12 () Int)
(declare-fun Q13 () Int)
(declare-fun Q14 () Int)

(declare-fun Q21 () Int)
(declare-fun Q22 () Int)
(declare-fun Q23 () Int)
(declare-fun Q24 () Int)

(declare-fun Q31 () Int)
(declare-fun Q32 () Int)
(declare-fun Q33 () Int)
(declare-fun Q34 () Int)

(declare-fun Q41 () Int)
(declare-fun Q42 () Int)
(declare-fun Q43 () Int)
(declare-fun Q44 () Int)



(assert (>= Q11 0))
(assert (<= Q11 1))
(assert (>= Q12 0))
(assert (<= Q12 1))
(assert (>= Q13 0))
(assert (<= Q13 1))
(assert (>= Q14 0))
(assert (<= Q14 1))


(assert (>= Q21 0))
(assert (<= Q21 1))
(assert (>= Q22 0))
(assert (<= Q22 1))
(assert (>= Q23 0))
(assert (<= Q23 1))
(assert (>= Q24 0))
(assert (<= Q24 1))


(assert (>= Q31 0))
(assert (<= Q31 1))
(assert (>= Q32 0))
(assert (<= Q32 1))
(assert (>= Q33 0))
(assert (<= Q33 1))
(assert (>= Q34 0))
(assert (<= Q34 1))


(assert (>= Q41 0))
(assert (<= Q41 1))
(assert (>= Q42 0))
(assert (<= Q42 1))
(assert (>= Q43 0))
(assert (<= Q43 1))
(assert (>= Q44 0))
(assert (<= Q44 1))


(assert (= (+(+ Q11 Q12) (+ Q13 Q14)) 1))
(assert (= (+(+ Q21 Q22) (+ Q23 Q24)) 1))
(assert (= (+(+ Q31 Q32) (+ Q33 Q34)) 1))
(assert (= (+(+ Q41 Q42) (+ Q43 Q44)) 1))



(assert (= (+(+ Q11 Q21) (+ Q31 Q41)) 1))
(assert (= (+(+ Q12 Q22) (+ Q32 Q42)) 1))
(assert (= (+(+ Q13 Q23) (+ Q33 Q43)) 1))
(assert (= (+(+ Q14 Q24) (+ Q34 Q44)) 1))



(assert (<= (+(+ Q11 Q22) (+ Q33 Q44)) 1))
(assert (<= (+(+ Q41 Q32) (+ Q23 Q14)) 1))

(assert (<= (+(+ Q21 Q12) 1)))
(assert (<= (+(+ Q31 Q22) Q13) 1))
(assert (<= (+(+ Q33 Q42) Q24) 1))
(assert (<= (+(+ Q43 Q34) 1)))

(assert (<= (+(+ Q13 Q24) 1)))
(assert (<= (+(+ Q23 Q12) Q34) 1))
(assert (<= (+(+ Q32 Q43) Q21) 1))
(assert (<= (+(+ Q42 Q31) 1)))


(check-sat)
(get-model)

(exit)

