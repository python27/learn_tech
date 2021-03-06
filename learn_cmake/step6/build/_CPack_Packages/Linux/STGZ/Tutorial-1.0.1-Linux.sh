#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --prefix=dir      directory in which to install
  --include-subdir  include the Tutorial-1.0.1-Linux subdirectory
  --exclude-subdir  exclude the Tutorial-1.0.1-Linux subdirectory
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "Tutorial Installer Version: 1.0.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
LICENSE
=======

This is an installer created using CPack (http://www.cmake.org). No license provided.


____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the Tutorial will be installed in:"
    echo "  \"${toplevel}/Tutorial-1.0.1-Linux\""
    echo "Do you want to include the subdirectory Tutorial-1.0.1-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/Tutorial-1.0.1-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

tail $use_new_tail_syntax +147 "$0" | gunzip | (cd "${toplevel}" && tar xf -) || cpack_echo_exit "Problem unpacking the Tutorial-1.0.1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� <��Q �ZpT��o��%l~���Q�8˲��M*	a��	`XA|n������ݷv�Ii3�A��cme,�2��i��Z�V����D�ZZ#�s޽o���F�Rۜ��}�����s�����5Թdou4�(�B���E.*Y�V{I�������
��좭�Vb/������V���VJD�ŭFj�FdW�Ҳ\���Ee���'�m��Ms��7fL�d+��`+-.����UI���bq���#�1@h��+,;]~��ˑuB?,�����d]�6���r��Z�j�+�Ղ $j,�4"p-�h�q��d�����X�����q��anw�z�ǡ#���y#|ɑ��Rz��bz/�L�I��%\����������v��#��G��x$�r����^,Rɣ�T�~�IdO��,5��=�	̱:,���=KO�8N���?~�Xe�� f���������m���3��n�����1�I!v���ٛw�����_b�OO_�ʔ_>�������3��g>������j=!TT�~l�QWZ�+����'�W�+��>�eX��*Ԝ�B����6�8�b�I,h������_��&��X9oM'�������A9:��t�Cb���R4�(�$�&P��\u��'�
�p��hl���#4 }��*�Lk32����Kdy@v5@,�i�U���E�����v�.bi�D 1D��P �	�,�=�YsL���q��x���+��޾�a�K��22��Jù�G�	)�x�G�	B���Af�'��z�Wq]���ʵ����ÙX\�p�|H�e�$�P�b�>ӕ��t���U�w3��˫�N#X��~ɵ�2�R�˗��(dpb3+��a�|~��d����ħ�Gq^���JӔ��Qǧ��Kt�I�Sځ�sb$�\�x�s���q�Y�㹍����#�;�ISK����Tl3TӇ1t�z�����a��'ƿ��L穁�!����Ψ
�\��Vp��n����^VT�����KlC������+ۧ:�MxZ�G��X��a��Ϊa��d%� A�_����x�F����f2��Pt1,��e�ˡrS6�ǌ&���E`�h��sA�2��c�������0���l޻��v��v�	�4H���o~�璚=������3\��A5�������Ho2�ɂr�V���y�a����P�xC��w=�����O�gΘ6���֡L=�����I:ǭ�4��UFc�2!\
a��/�w�z��%>�VL���<�Fl�މ����EG�_��~�w-ʻs��+�[�Q�9������ì������ܷH�'��8��J���߫�W�俀еŨq9�C�0����n]g4ѓ-���	�X�x��W#���AxG�*�&�1x�o7�k�0�oo��h�7�l�x�Z���⼄��	�}����Tyَ} �ѓf�$5BA	w'Y��4�n����Ȟp���x"D�q�InO�%;�������(K)��و���������O�lwɡ��/Ig��|A5�1��|A�<�͙�-H�@U���z �!��E��2��3�Y�53��"����ubP��3$���[�͵�/5���X��t^��-��%��`�+c�1��W����W��ؚ�rz/.���%��R#��&6���?��t� s�����c)^�b�n��Ҽ��m�����o�N�����|�⤼y��V� ���N�o�#�>	gb�̰{w�Ģ���(o�1���(�:�ݹ^����R�{�����k�C�����.E���NU�0*����8�4:ZA�zW@���c�p���έ9��P��j=.M�%P����'�?��<���7	+��C�#g+�y�1�،M����wB_�;�ٳ�x�J_b�M ݉j�� (��ء<�7@2<�Ş���{aS&�*y@b���F!{uc��`~X�о�Ĳ Gͅ[p38�e�]ŜcY �ֲ���\�B;m���Ԗ���,�ߋ���_��|^�?ߺ��f�ޣ���L�9a���aM\�`�t�3X׎�����ɇYd���M�Ahl�p��蛱��.-�>������y����ړ.g����w�������BA��m)pg�W�g��`4��	g��#F�1
�&
_��O|U+�pe�T|���m�npB<:��3wA��&�"\�/��$n��s��>���! �T�e��=B6���WL�X�-�+ � e�Y��|<�X>P~�	uHe�:��Pus%�Y�ui�Y9k��Y���9YV��\H��>���2��5���m��>�0_г!M�~�!�!�v�<�_Y��;����4���
��c	}���+|�?9m��&�c�bpׄx��&<F��Z�~y)+S��m�o��s-�pܑ��F~�C�������6t��8	a]OC��j��x���g�{!��	��֮�*�]<�;	R#��I6+���j+��`+[��l�{\τ/t�#�na��5�dW3㚃QKC��|��(����{y�����UE�Ha�U �h��X <��By_%\��A��I�jH�pص�j��w6��J��F(8$+�h)��C�x|	���Z��@�J�m`<�v
�)�!�@R�6�8�����S���u�ph�L�p�����o|�b�#՛��i!�kq�^���:շ�vqV.�3�X�r���2B�&~��<h����EB��p����H�÷_���~0��C���=H�^&ܯ��S��:W�
���p9��á��.iZR����˔���r7��|A�v��q8u�y��)����.��o��'�d
�� d:Ɗ�.;)�q/A�f8��̓�^#I�>fs�e}�8�F���O�8l�I.?�M��C��� /��m]"�Z9���3$��gaW���T��D��C�2��r�޷4H�b�o�_�&`B�"t��66�G8���oH�)u`(o���%xZ¶O{���Ո������;��i�'x�H��1��Ӕ��C�S�]g�Ϥ巩|��oO��
���tU�	~�Syj�7'x�c�$x�*�M�t%$x�Kܢ�+����Pq�KxJ�ے�;j���|����o��[ >���]V�h���byR��*?@1'��x#�q�M\�;u�٫����w���Hr\W�ÿ�d��f1'�[��(<綨�c�5B����B!Y_�O�6g����!�x,�6� � B����o�6�G�Mz���I?��#~�.����&X������8�����~�AkӿΠ��O2hm�%�Ϳڠ����6�[�=�̠��}:�OZ�>i�9��di$�4��^����$���Kr@jD�{��H�$wHj��\~�-���m%p#k�{d��b/./J��7=	no�����@`9�p��� 2���������KRu}e�Cr̙��E��^n�4{d��Q����2K*h�F�;����3o�SYWS��1��䬫R3�U;wFe�4��z��)9+g�:�s�_����AusJ�\+��B�9��QQ��N0	�����
���d�*%}�Ò�ՃN�Ҡ�Z��/�菺=��? �^x@���'�T������?���!���A0aֈt2�u�Ԍ��� ��_�PU(��k����������O��2kq����:h��G�GT�_Z訟_3w�TW9{n�h�P3 �`�|�Twk]�󦌌���� ě*:�ڹ�ĉ����E�0���!�!��O�73<�U 6  