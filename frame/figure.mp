input metauml;
beginfig(1);
  Class.A("Point") ("+x: int", "+y: int") ();

  Class.B("frame_base") ("+unwind: struct frame_unwind *")
    ("+this_base(this_frame: struct frame_info, this_base_cache: void **): CORE_ADDR",
      "+this_locals(this_frame: struct frame_info, this_case_cache: void **):CORE_ADDR",
      "+this_args(this_frame: struct frame_info, this_case_cache: void **):CORE_ADDR");

topToBottom(45)(A, B);

drawObjects(A, B);

clink(aggregationUni)(A, B)

endfig

end
