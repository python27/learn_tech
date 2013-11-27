function [ND, eigenvalue] = getDriverNodeNumber(A)
% ��������һ�������״̬����A��������ȫ���Ƹ���������Ҫ�������ڵ�ĸ���
%
% ���룺�����״̬����A��һ��Ϊ�ڽӾ����ת�þ���
% �����1. ���Ƹ�������Ҫ�����������ڵ�ĸ���
%       2. ��Ӧ������ֵ
% 
% ע�⣺�ڵ�ı��Ϊ1,2,3,...,N
%
% �㷨��Դ��
% Paper: Exact controllbility of complex network
%        DOI: 10/1038/ncomms3447
%
% ���ߣ����·� (lixinfeng@zju.edu.cn)
% ʱ�䣺2013/11/21

N = size(A, 1);

% ��������ֵ
d = eig(A);
% ��ȡ��λ����
e = eye(N);

ND = -1;
dsize = size(d, 1);

% �������п��ܵ�u(\lambda) �ҵ���������
for i = 1:dsize
    curAns = N - rank(d(i) * e - A);
    if (curAns > ND)
        ND = curAns;
        eigenvalue = d(i);
    end
end

end