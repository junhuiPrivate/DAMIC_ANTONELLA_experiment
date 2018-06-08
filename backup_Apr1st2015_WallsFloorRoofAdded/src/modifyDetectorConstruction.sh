# /usr/local/bin/bash

#*#*# outline #*#*#
### 1)Scanning /app/web/damic/tmp_files/environment_overscan_rootfiles/..., to check if there are 18 new fileshave been transferred from DES05 machine.
### 2)If 18 new files are available, create 3 new direcotries named after runID under /app/web/damic/monitoring, under each directory, create its sub-direcotyies and sun-index.html. The names of directories are based on a text file : brief_monitor_terms.txt .
### 3)Copy transferred files to appreciate directories depend on their runIDs.
### 4)Modify the "main" index file under /app/web/damic/monitoring, increasing an entry on the main monitroing page.
### 5)Modify all of the sub-index.html files.
### 6)Doing above 1) to 5) automatically by cron. 

#*#*# technical details #*#*#
###0. Read the text file : brief_monitor_terms.txt.
###1. make directories according to records in the above text file.
###2. copy files to correct directories. 
###3. modify the key words in the template file according to a fits file name.
###3. copy the lines of this modified template file into the main and sub index.html files after a tag.



 suffix_fits=".fits"
 suffix_root=".root"
 template_index_file="template_index_directory/index.html"
 slash="/"
 intwindow="s-IntW"
 match="sampleroot"
 match_entry="fits_file_entry"
 ###inotifywait -m ../rootfiles/ --fromfile %w%f -e create |
 ###inotifywait ../rootfiles/ --fromfile --format{%w%f} -e create |
### http://unix.stackexchange.com/questions/24952/script-to-monitor-folder-for-new-files 
 ###inotifywait -m ../rootfiles/ 2>&- | awk '$2 == "CREATE" { print $3; fflush() }' | 
    while read file; do
        echo "$file" ### This $file is a root file transferred from des05 machine.
        filename_without_directory=${file##* } ### "../rootfile, EXECUTE" was rejected, only "$file" is there.
        filename_without_suffix=${filename_without_directory%%.*} ### kick off the suffix(.root) of "$file"
        echo "$filename_without_suffix"
        ##### one version to get two numbers of a root file name, int and exp . 
        ###grep -Po "(?<=Int-)\d+|(?<=Exp-)\d+" <<< "$filename_without_suffix" | paste - - | while read n1 n2
        ###    do
        ###    echo "int = $n1; flaflag;  exp = $n2"
        ###    done

        ##### Another version to get two numbers of a root file name, int and exp . 
        int=${filename_without_suffix#*Int-}
        int=(${int//[a-z_-]/ })
        exp=${filename_without_suffix#*Exp-}
        exp=(${exp//[a-z_-]/ })
        echo "int = $int; exp = $exp"
        table_key_words_monitoring_mainpage="$exp${intwindow}${int}" ### get a string like "5000s-IntW300"
        echo "The key words of table name in mainpage is : $table_key_words_monitoring_mainpage"
        directory_name="$filename_without_suffix${suffix_fits}" 
        echo "$directory_name"

        #####  modify the key words in the template file according to a input filename.
        sed "s/$match_entry/$directory_name/g" ./template_index_directory/one_entry_table_template.html > modified_one_entry_table.html
        ###sed "s/$match_entry/$directory_name/g" ./template_index_directory/one_entry_table_template_NG.html > modified_one_entry_table.html
        ###echo "$table_key_words_monitoring_mainpage"

        ### The following line try to find a place with the matched string "$stable_key_words..." in (main) index.html file, and insert the "modified_one_entry_table" after the matched string in the "index.html".
        sed -i -l 2 "/$table_key_words_monitoring_mainpage/r modified_one_entry_table.html" index.html
        #sed -f sed2lines.txt index.html
         ###sed -i.bak "/^Stackoverflow/r "fileB"" fileA 
        ###sed -e "1,/$table_key_words_monitoring_mainpage/d" ./index.html 

       ##### create a directory of "filename.fits", copy a (sub)index.html and modify it.
        dir_index_html="IndexFiles"
        cd $dir_index_html
        mkdir $directory_name
        cp ../template_index_directory/index.html $directory_name${slash}
        directory_rootfiles="$filename_without_suffix${suffix_root}" 
        sed -i "s/$match/$directory_rootfiles/g" ./$directory_name${slash}index.html ### change the line containing "sampleroot" with "filename.root" in (sub)index.html, "-i" modify the file "in place".  
        exit 
    done
