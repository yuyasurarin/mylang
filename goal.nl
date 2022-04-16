// draft of my lang

!fn:a(int:n) = {
    !int:num = n;
    rt;
}
!fn:b(int:n;int) = {
    rt:n;
}
!fn:main() = {
    a(int:10);
    !int:num;
    {num += b(int:4);}.while(num<50);
}
!class:c = {
    !fn:c() = {
    }
    !fn:ta(;int) = {
        rt:{int:10};
    }
}