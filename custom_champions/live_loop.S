.name "live_loop"
.comment "LiVe_LoOp"

add r3, r3, r3
label:
    live %1
    zjmp %:label