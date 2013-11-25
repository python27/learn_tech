function nodes = getDriverNode(A)
% ��������һ�������״̬����A,�����ܹ����Ƹ���������нڵ�ļ���
%
% ���룺�����״̬����һ��Ϊ�ڽӾ����ת�þ���
% ��������Ƹ���������Ҫ�����������ڵ㼯��
%
% ע�⣺�ڵ�ı��Ϊ1,2,...,N
%
% �㷨��Դ��
% Paper: Exact controllbility of complex network
%        DOI: 10/1038/ncomms3447
%
% ���ߣ����·�(lixinfeng@zju.edu.cn)
% ʱ��: 2013/11/21

    % �õ�����size�����ɵ�λ���󣬼��������ڵ����������Ӧ������ֵ
    sizeA = size(A, 1);
    eyeMatrix = eye(sizeA);
    [nd, eigenvalue] = getDriverNodeNumber(A);
    
    % �����м���� A - lambda * I
    ansMatrix = A - eigenvalue * eyeMatrix;
    
    % �����г��ȱ任�ȼ��ڼ���ת�þ�����г��ȱ任
    rotateMatrix = rref(ansMatrix');
    independentIndex = zeros(1, sizeA);
    
    % ȡ����������޹�����������Ӧ��index
    for i = 1:sizeA
        for j = i:sizeA
            if (rotateMatrix(i, j) ~= 0)
                independentIndex(j) = 1;
                break;
            end
        end
    end
    
    % ȡ�������õ��������������Ӧ��index����Ϊ����
    % �ڵ��index
    nodes = find(independentIndex == 0);   
end