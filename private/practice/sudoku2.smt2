(declare-datatypes () ((N N1 N2 N3 N4 N5 N6 N7 N8 N9)))

(declare-const n11 N)
(declare-const n12 N)
(declare-const n13 N)
(declare-const n14 N)
(declare-const n15 N)
(declare-const n16 N)
(declare-const n17 N)
(declare-const n18 N)
(declare-const n19 N)

(declare-const n21 N)
(declare-const n22 N)
(declare-const n23 N)
(declare-const n24 N)
(declare-const n25 N)
(declare-const n26 N)
(declare-const n27 N)
(declare-const n28 N)
(declare-const n29 N)

(declare-const n31 N)
(declare-const n32 N)
(declare-const n33 N)
(declare-const n34 N)
(declare-const n35 N)
(declare-const n36 N)
(declare-const n37 N)
(declare-const n38 N)
(declare-const n39 N)

(declare-const n41 N)
(declare-const n42 N)
(declare-const n43 N)
(declare-const n44 N)
(declare-const n45 N)
(declare-const n46 N)
(declare-const n47 N)
(declare-const n48 N)
(declare-const n49 N)

(declare-const n51 N)
(declare-const n52 N)
(declare-const n53 N)
(declare-const n54 N)
(declare-const n55 N)
(declare-const n56 N)
(declare-const n57 N)
(declare-const n58 N)
(declare-const n59 N)

(declare-const n61 N)
(declare-const n62 N)
(declare-const n63 N)
(declare-const n64 N)
(declare-const n65 N)
(declare-const n66 N)
(declare-const n67 N)
(declare-const n68 N)
(declare-const n69 N)

(declare-const n71 N)
(declare-const n72 N)
(declare-const n73 N)
(declare-const n74 N)
(declare-const n75 N)
(declare-const n76 N)
(declare-const n77 N)
(declare-const n78 N)
(declare-const n79 N)

(declare-const n81 N)
(declare-const n82 N)
(declare-const n83 N)
(declare-const n84 N)
(declare-const n85 N)
(declare-const n86 N)
(declare-const n87 N)
(declare-const n88 N)
(declare-const n89 N)

(declare-const n91 N)
(declare-const n92 N)
(declare-const n93 N)
(declare-const n94 N)
(declare-const n95 N)
(declare-const n96 N)
(declare-const n97 N)
(declare-const n98 N)
(declare-const n99 N)

; column
(assert (distinct n11 n12 n13 n14 n15 n16 n17 n18 n19))
(assert (distinct n21 n22 n23 n24 n25 n26 n27 n28 n29))
(assert (distinct n31 n32 n33 n34 n35 n36 n37 n38 n39))
(assert (distinct n41 n42 n43 n44 n45 n46 n47 n48 n49))
(assert (distinct n51 n52 n53 n54 n55 n56 n57 n58 n59))
(assert (distinct n61 n62 n63 n64 n65 n66 n67 n68 n69))
(assert (distinct n71 n72 n73 n74 n75 n76 n77 n78 n79))
(assert (distinct n81 n82 n83 n84 n85 n86 n87 n88 n89))
(assert (distinct n91 n92 n93 n94 n95 n96 n97 n98 n99))

; row
(assert (distinct n11 n21 n31 n41 n51 n61 n71 n81 n91))
(assert (distinct n12 n22 n32 n42 n52 n62 n72 n82 n92))
(assert (distinct n13 n23 n33 n43 n53 n63 n73 n83 n93))
(assert (distinct n14 n24 n34 n44 n54 n64 n74 n84 n94))
(assert (distinct n15 n25 n35 n45 n55 n65 n75 n85 n95))
(assert (distinct n16 n26 n36 n46 n56 n66 n76 n86 n96))
(assert (distinct n17 n27 n37 n47 n57 n67 n77 n87 n97))
(assert (distinct n18 n28 n38 n48 n58 n68 n78 n88 n98))
(assert (distinct n19 n29 n39 n49 n59 n69 n79 n89 n99))

; square
(assert (distinct n11 n12 n13
                  n21 n22 n23
                  n31 n32 n33))

(assert (distinct n41 n42 n43
                  n51 n52 n53
                  n61 n62 n63))

(assert (distinct n71 n72 n73
                  n81 n82 n83
                  n91 n92 n93))

(assert (distinct n14 n15 n16
                  n24 n25 n26
                  n34 n35 n36))

(assert (distinct n44 n45 n46
                  n54 n55 n56
                  n64 n65 n66))

(assert (distinct n74 n75 n76
                  n84 n85 n86
                  n94 n95 n96))

(assert (distinct n17 n18 n19
                  n27 n28 n29
                  n37 n38 n39))

(assert (distinct n47 n48 n49
                  n57 n58 n59
                  n67 n68 n69))

(assert (distinct n77 n78 n79
                  n87 n88 n89
                  n97 n98 n99))

; initial condition
(assert (= n12 N9))
(assert (= n16 N7))
(assert (= n17 N4))
(assert (= n18 N8))
(assert (= n19 N5))

(assert (= n21 N5))
(assert (= n23 N2))
(assert (= n25 N4))
(assert (= n26 N6))
(assert (= n27 N3))
(assert (= n29 N1))

(assert (= n31 N7))
(assert (= n35 N3))
(assert (= n36 N8))
(assert (= n37 N9))
(assert (= n39 N2))

(assert (= n41 N9))
(assert (= n43 N4))
(assert (= n45 N6))
(assert (= n49 N8))

(assert (= n52 N1))
(assert (= n54 N8))
(assert (= n55 N9))
(assert (= n56 N2))
(assert (= n57 N5))
(assert (= n59 N3))

(assert (= n62 N3))
(assert (= n67 N7))
(assert (= n68 N9))
(assert (= n69 N6))

(assert (= n72 N6))
(assert (= n73 N3))
(assert (= n74 N1))
(assert (= n76 N9))
(assert (= n77 N2))
(assert (= n78 N5))
(assert (= n79 N7))

(assert (= n86 N4))
(assert (= n87 N8))
(assert (= n88 N3))

(assert (= n92 N2))
(assert (= n94 N3))
(assert (= n95 N7))
(assert (= n96 N5))
(assert (= n97 N6))
(assert (= n98 N1))
(assert (= n99 N4))

(check-sat)

; answer
(echo "column 1 ...")
(eval n11)
(eval n12)
(eval n13)
(eval n14)
(eval n15)
(eval n16)
(eval n17)
(eval n18)
(eval n19)

(echo "column 2 ...")
(eval n21)
(eval n22)
(eval n23)
(eval n24)
(eval n25)
(eval n26)
(eval n27)
(eval n28)
(eval n29)

(echo "column 3 ...")
(eval n31)
(eval n32)
(eval n33)
(eval n34)
(eval n35)
(eval n36)
(eval n37)
(eval n38)
(eval n39)

(echo "column 4 ...")
(eval n41)
(eval n42)
(eval n43)
(eval n44)
(eval n45)
(eval n46)
(eval n47)
(eval n48)
(eval n49)

(echo "column 5 ...")
(eval n51)
(eval n52)
(eval n53)
(eval n54)
(eval n55)
(eval n56)
(eval n57)
(eval n58)
(eval n59)

(echo "column 6 ...")
(eval n61)
(eval n62)
(eval n63)
(eval n64)
(eval n65)
(eval n66)
(eval n67)
(eval n68)
(eval n69)

(echo "column 7 ...")
(eval n71)
(eval n72)
(eval n73)
(eval n74)
(eval n75)
(eval n76)
(eval n77)
(eval n78)
(eval n79)

(echo "column 8 ...")
(eval n81)
(eval n82)
(eval n83)
(eval n84)
(eval n85)
(eval n86)
(eval n87)
(eval n88)
(eval n89)

(echo "column 9 ...")
(eval n91)
(eval n92)
(eval n93)
(eval n94)
(eval n95)
(eval n96)
(eval n97)
(eval n98)
(eval n99)
