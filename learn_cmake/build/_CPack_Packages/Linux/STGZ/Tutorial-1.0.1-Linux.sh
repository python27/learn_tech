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
This is the open source License.txt introduced in CMake/step6

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

tail $use_new_tail_syntax +143 "$0" | gunzip | (cd "${toplevel}" && tar xf -) || cpack_echo_exit "Problem unpacking the Tutorial-1.0.1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� ��Q �Z}l��]���sv.$�Cؖ3rRr��8� ���#�Sa_�G(��ݞ���l����ˤ�(JK� �
���"@UJ�6�@�j�TT�RB	�]�ʇ����������P!�~ �����{3ofgfg�x0-7�򺢦���R0\�v-<�nm��1�"-�u|(jY�fm˺`��Z"�5�~Y9S^�E\ɍ�)E���_�icx����=]��e�T����<-�^L�[O�I��,'U��0@< UBT9v�AZ�Sǘd$�E�W����g�=
z�&��Te�Y`^�{A�td�*���SP7R;��]߻z�j!W�<H-f{,��������Q���j�վ�Lz�9�X�I��ဦ�T�3��z��}Mˬ7�]j��~���W��w�sr�",�F�QWmb`�}d�k��z8�v/�m@]-��@����������y`���7x���o�s���y�����4�����=?���C�y����^�[]y���g���L��C��{er�L��ُ��7��5�>6l��/1�!�	�f[^F��2@�>Z�	����K���xȢQ-y�бOL�m��)�?������y�6�c����O�{��#����[���,�*��������Kj[F�4I#Bg�[HH���n�(�3�ͩ�A���!���b��Bg/T�H�B^���ND]I�dNM�z�B��TVL�VN\�ɴ�&��u��Q��%9A�dNH�	�AM3q��:[ۄp�Z�Ycա�1�X���s���ӵ8c>2�A}�1ƨ����0W�X:>*��~ _ �98�9��z�5 ��6P���{'��|�2B�
��bq�q�rj�^�l���lq-V�F�9F��XK
�O�U�kK�n��!c�)ty��!c�)\��2z���N1��m�oΜ���p\�p�ް-�cp�Q |�w�����[8Wu'��$N(��u���L�IΏ��W&��W�cM��9v����9��sy0|�0|�2m�s��h��U���vly~���L��^��<�'��y�%@��[~\l���czL�u�A͙���`�f��X�w������~���4�c7}1����<_,�Ж��v���� �sc���7o��o�5��T*7e@f>Cy+-�{��w�����z㶁)��L>	/�0�0������L=�i�x�@�q��Ev_Q_���O�v�ݿ~�j?��[�w�>���K�5��o^h�~����jǝ��ɱ?������AYa��4j�6I�Ҋ�7&���U��kyP��젤�=%��yQ�xUQt^I�C|Z��c~-���,~��Д.�9h|e�t���qM=�4��4���~���0˽w����L���l��nY�P����]�*��:�7 ���p�$�:�>����}�E(���,��|m}��{�"Z���E�*{�얺��1	�� r2Zǽ���a\�����\����<�̧�4���|�*����ӽ�	n19~�a�h���L�{�e�M�rB�`�!���?>_T&༉�ǽ�k���y��yh!�ߘ�ͺ��L�гA��J<n_
4{����ֹ	���(|��	ȇO���g��}m�Mx~�����]@��=������v-ߴu0/��殴,�
�X����J*_ 	�Y
:������p��z�)���&#������6���A�Jy�z�Ӊ��H@Vt)m�\��C�4$���4���	bH)QK�@bD��(�U��E�B.A ��8����X!d�4���'�*��' ���*f%!�PK�DUG���|{\5���8T������'$�+٬$�_��x�1�c���0t�X�:�_Ih� qFl�܇Y����������T>1� ��	���+8�B�>�p>��!g�sR��l#�>���[A�My;n��>�������^֤����?�Mpt?Ye�v�Eh\�p��p�g;p"8�������:p���b=�~�+��\��*�~�J>��������g�8L?t�p�zyAi�q��)��m�\��'8#V�q�rܳ��� �s�~�&c��ugQI�������p}�.�{ݬqxx�\ ���'�3b��J�B��팣<���QҴ��7� ~��8�A�>ZO������ͦ2�U��fyV�q;8+�����L�\��Y�1�H�%����fּ�.+oc CgL�<�zD{�J�2-�-�&l���T���*ӷg}�*hDԘ�T�=8c�Ն<k�Ƒ֎�U+��T��Q[�5d+vWAh���-/2d�'T��r�-���G-�"C�l���[�'g�-ә<k˗��X���r�!o��eę*`��|o���u��@�hq�l?��5ַ�$G�����H�a��$�c�}��oY����@+��?���~1y��_R���J�}�����vĲ�'K�R3��+���2��/�ɔ�����gܱ�AGx��w,z�qǶ�wl�������{�qǲO8�8��\&��c�뎝W�n�%�;��u����;�aݱ�V���(��^V��2�>�K'qU��|2�A���/tu���bゞ���Y��P���2(f����� �	�rI��Ț��ABi''��L!t��g�#`␄�Є���j ><؍��������F3��td}$0$�B..詼�30��蠦)QN`����hwg�f��c�mV᛺z[�]B�ƍ1!m��>����g���S���6�}��k�Jw�݃3k���p�̚�=��pR�y�Ws\������*ԓ�LJ��L>!��Ц���P ��#FZZ.t������H$:�����O��f��q��U)�+9N���I����4>���5Dj�LH0�%;C���?���#tG�����t�  XӼ��2/��:�!t���m�W5�Ԁ;	E��rQ�z�|NUv�/��2����q�����6G�u]�����܎��0�����i>ͧ�����	m@�t (  