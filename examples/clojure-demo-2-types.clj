; Data types: java strings

"abc"

; (java ) chars

\a
\b
\c

; Numbers

123
3.14159

; Big numbers long/BigInteger

(* 99999999 (BigInteger. "999999999999999"))

; Symbols refer to things

(def y 99)

y      ; is a symbol, refers to 99
max    ; is a function
+      ; so is +
java.lang.String


; Keywords refer to themselves

:first_name
:last_name
:import


; A list is a first/rest pair

'( a b c (d e (f g) h i ) j )


; Bind it to a name

(def x '( a b c (d e (f g) h i ) j ))

; Get the first item of the list

(first x)

; Get everything but the first

(rest x )

; concatenate it to another list

(concat x '( 1 2 3 ))

; Add an element to the front

(cons 1 x)


; A vector is more or less an array list

[ 1 2 3 ]

(first [1 2 3])
(rest [1 2 3])

; A hash maps names->values

{ :fname "russ" :lname "Olsen"}

(def h { :fname "russ" :lname "Olsen"} )

(:fname h)

(assoc h :age 10 )



; The critical thing about LISP and clojure is
; that the code and the data are the same thing:

(def p '(println "Hello from this bit of clojure"))

(eval p)

(def p '(defn say-hello [] (println "hello out there")))

(eval p)

; Evaluating clojure code
; Many things evaluate to themselves

1
:foo
"hello"
p
concat

; Feed clojure a list and it will take the first
; item of the list as a function and try to
; evaluate the function using the rest as
; arguments

(foo 1 2 3)  ; no function

(max 1 2 3)  ; yes!


