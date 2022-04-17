// draft of my lang

!fn:void:a(num:n) = {
    !num:n = n+10;
    rt;
}
!fn:num:b(num:n) = {
    rt:n;
}
!fn:void:main() = {
    a(num:10);
    !num:n;
    n = 0;
    {n += b(num:4);}.while(n<50);
}
!class:c = {
    !fn:void:c() = {
    }
    !fn:void:ta() = {
        rt:10;
    }
}