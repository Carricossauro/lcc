module BTree

open Cp

// (1) Datatype Definition -----------------------------------------------------

type BTree<'a> = Empty | Node of 'a * (BTree<'a> * BTree<'a>)

let inBTree x = either (konst Empty) Node x

let outBTree x = 
    match x with
    | Empty -> i1 ()
    | Node (a,(b1,b2)) -> i2 (a,(b1,b2))

// (2) Ana + cata + hylo -------------------------------------------------------

let baseBTree g f x = (id -|- (g >< (f >< f))) x

let recBTree f x = (baseBTree id f) x       // Isto é, id -|- (id >< (f >< f)) 

let rec cataBTree a x = (a << (recBTree (cataBTree a)) << outBTree) x

let rec anaBTree a x = (inBTree << (recBTree (anaBTree a)) << a) x

let hyloBTree a c x = (cataBTree a << anaBTree c) x

// (3) Map ---------------------------------------------------------------------

// instance Functor BTree
//			where fmap f = cataBTree (inBTree . baseBTree f id)
let fmap f x = (cataBTree (inBTree << baseBTree f id)) x

// (4) Examples ----------------------------------------------------------------

// (4.1) Inversion (mirror) ----------------------------------------------------

let invBTree x = cataBTree (inBTree << (id -|- (id >< swap))) x

// (4.2) Counting --------------------------------------------------------------

let countBTree x = cataBTree (either zero (succ << uncurry (+) << p2)) x

// (4.3) Serialization ---------------------------------------------------------

let inord x =
    let join (x,(l,r)) = l @ [x] @ r
    in either nil join x

let inordt x = (cataBTree inord) x

let preord x =
    let join (x,(l,r)) = [x] @ l @ r
    in either nil join x

let preordt x = (cataBTree preord) x

let postordt x =
    let join (x,(l,r)) = l @ r @ [x]
    in (cataBTree (either nil join)) x

// (4.4) Quicksort -------------------------------------------------------------

let rec part p x =
    match x with
    | [] -> ([],[])
    | (h::t) ->
        let (s,l) = part p t
        in if p h then (h::s,l) else (s,h::l)

let qsep x =
    match x with
    | [] -> i1 ()
    | (h::t) ->
        let y = part ((<) h) t
        in i2 (h,y)

let qSort x = (hyloBTree inord qsep) x

// (4.5) Traces ----------------------------------------------------------------

let cons a t = a::t

let union x y = x @ y

let traces x = 
    let tunion (a,(l,r)) = (List.map (cons a) l) @ (List.map (cons a) r) 
    in cataBTree (either (konst [[]]) tunion) x

// (4.6) Towers of Hanoi -------------------------------------------------------

let present x = inord x

let strategy x =
    match x with
    | (d,0) -> i1 ()
    | (d,n) -> i2 ((n-1,d),((not d,n-1),(not d,n-1)))

let hanoi x = (hyloBTree present strategy) x

// (5) Depth and balancing (using mutual recursion) ----------------------------

let balDepth x =
    let h (a,((b1,b2),(d1,d2))) = (b1 && b2 && abs(d1-d2)<=1,1+max d1 d2)
    in
        let f ((b1,d1),(b2,d2)) = ((b1,b2),(d1,d2))
        in
            let g x = (either (konst (true,1)) (h << (id >< f))) x
            in cataBTree g x

let balBTree x = (p1 << balDepth) x

let depthBTree x = (p2 << balDepth) x

// Fim do module BTree