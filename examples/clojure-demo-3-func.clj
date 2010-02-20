
; create a new namespace and import java.io.File

(ns russ (:import java.io.File))

; Now I can refer to it as just File instead of java.io.File

File

; Make a new File, dot goes at the end, double quotes

(File. "/etc")

; Bind the new file object to a name

(def x (File. "/etc"))


; Now you can list all the files (java api)

(.listFiles x)

; Turn this from a java array to a sequence

(seq (.listFiles x) )


; Or you can see if this file is a directory (java api)

(.isFile x)

; Turn that into a function

(defn file? [f] (.isFile f))

; You can also get the file length

(.length x)

; turn that into a function

(defn file-len [f] (.length f))

; Map - call a function on all elements of a seq

(map file? (.listFiles x))

; Also do it with file lengths

(map file-len (.listFiles x))

; But the length of directories doesn't make much sense, but we can use filter!

(filter file? (.listFiles x))

; Now we can get the list of file lengths

(map file-len (filter file? (.listFiles x)))

; We can use reduce to add them all together

(reduce + (map file-len (filter file? (.listFiles x)))

; The turn this into a function

(defn total-length [f] 
  (reduce + (map file-len (filter file? (.listFiles f)))
