(set-logic QF_LIA)
(declare-fun NT () Int)
(declare-fun QI () Int)
(declare-fun NS () Int)
(declare-fun V () Int)
(declare-fun SA () Int)
(declare-fun WA () Int)

(declare-fun T () Int)



(assert (>= NT 1))
(assert (<= NT 3))


(assert (>= QI 1))
(assert (<= QI 3))

(assert (>= NS 1))
(assert (<= NS 3))

(assert (>= V 1))
(assert (<= V 3))


(assert (>= SA 1))
(assert (<= SA 3))

(assert (>= WA 1))
(assert (<= WA 3))

(assert (>= T 1))
(assert (<= T 3))


(assert (not(= NT WA)))
(assert (not(= NT SA)))
(assert (not(= NT QI)))

(assert (not(= WA SA)))

(assert (not(= SA QI)))
(assert (not(= SA NS)))
(assert (not(= SA V)))

(assert (not(= QI NS)))

(assert (not(= NS V)))
(assert (not(= V T)))

(check-sat)
(get-model)

(exit)
