(ns clj-tests
  (:use clojure.contrib.test-is)
  (:use clojure.contrib.shell-out))

(defn windows? []
  (re-seq #"[wW]indows" (System/getProperty "os.name")))

(defn executable [name]
  (if (windows?)
    (str name ".exe")
    name))

(defn run [cmd]
  (apply sh 
    (cons
      (executable (first cmd))
      (rest cmd))))

(defn output-matches? [cmd re msg]
  (let [ output (run cmd) ]
    (is
      (re-seq re output)
      msg)))

(defn output-doesnt-match? [cmd re msg]
  (let [ output (run cmd) ]
    (is
      (not (re-seq re output))
      msg)))

; core jar files and main classes

(output-matches? ["clj" "-debug"] #"lib.clojure\.jar" "Contains clojure.jar")
(output-matches? ["clj" "-debug"] #"lib.clojure-contrib\.jar" "Contains contrib")
(output-matches? ["clj" "-debug"] #"lib.jline\.jar" "Contains jline.jar")
(output-matches? ["clj" "-debug"] #"jline\.ConsoleRunner" "Contains console runner")
(output-matches? ["clj" "-debug"] #"clojure\.main$" "contains clojure main")

; repl class

(output-doesnt-match? ["clj" "-debug" "-repl-class" "foo"] #"clojure\.main$" "repl class")
(output-matches? ["clj" "-debug" "-repl-class" "foo"] #"foo$" "repl class")

; clojure args

(output-matches? ["clj" "-debug" "arg1" "arg2"] #"arg1 +arg2$" "clojure arguments")
(output-matches? ["clj" "-debug" "--" "arg1" "arg2"] #"arg1 +arg2$" "-- params")

; No jline

(output-doesnt-match? ["clj" "-debug" "-no-jline"] #"jline.jar" "no jline, no jar")
(output-doesnt-match? ["clj" "-debug" "-no-jline"] #"jline.ConsoleRunner" "no jline no class")

; -classpath and -cp

(output-matches? ["clj" "-debug" "-cp" "extra" ] #"extra" "-cp")
(output-matches? ["clj" "-debug" "-classpath" "extra" ] #"extra" "-classpath")

; Java args

(output-matches? ["clj" "-debug" "-Dfoo=bar" ] #"-Dfoo=bar.*clojure.main" "-D")
(output-matches? ["clj" "-debug" "-Xfoo=bar" ] #"-Xfoo=bar.*clojure.main" "-X")
(output-matches? ["clj" "-debug" "-server" ] #"-server.*clojure.main" "-server")
(output-matches? ["clj" "-debug" "-client" ] #"-client.*clojure.main" "-client")
(output-matches? ["clj" "-debug" "-hotspot" ] #"-hotspot.*clojure.main" "-hotspot")




