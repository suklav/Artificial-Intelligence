(set-logic QF_LIA)

(declare-const c11 Int)
(declare-const c12 Int)
(declare-const c13 Int)

(declare-const c21 Int)
(declare-const c22 Int)
(declare-const c23 Int)

(declare-const c31 Int)
(declare-const c32 Int)
(declare-const c33 Int)


(assert(>= c11 1))
(assert(<= c11 3))

(assert(>= c12 1))
(assert(<= c12 3))

(assert(>= c13 1))
(assert(<= c13 3))

(assert(>= c21 1))
(assert(<= c21 3))

(assert(>= c22 1))
(assert(<= c22 3))

(assert(>= c23 1))
(assert(<= c23 3))


(assert(>= c31 1))
(assert(<= c31 3))

(assert(>= c32 1))
(assert(<= c32 3))

(assert(>= c33 1))
(assert(<= c33 3))



(assert (distinct( c11 c12 c13)))
(assert (distinct( c21 c22 c23)))
(assert (distinct( c31 c32 c33)))

(assert (distinct( c11 c21 c31)))
(assert (distinct( c12 c22 c32)))
(assert (distinct( c13 c23 c33)))

(check-sat)
(get-model)

(exit)


