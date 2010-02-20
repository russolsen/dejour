; Strings just like java

"hello world"

; Print a string

(println "hello world")

; Create a function to print

(defn say-hello [] (println "hello world"))

; and call the function

(say-hello)

; A function with an argument

(defn say-it [msg] (println msg))

; Create a text file hello.clj with

(println "hello world")

; Run it with clj hello.clj

; Clojure strings are java strings...

(.toUpperCase "hello world")

; Programming logic

(if (> 10 11) "bigger" "smaller")

; Programming logic in a function

(defn bigger? [a b] (if (> a b) "bigger" "smaller"))

; Back to slides...
