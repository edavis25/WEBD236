<?php
include_once 'models/File.inc';

class UploadDir {
    private $dir;

    function __construct($dir = 'uploads') {
        $this -> dir = getcwd() . DIRECTORY_SEPARATOR . $dir;
        if (!is_dir($this -> dir)) {
            mkdir($this -> dir);
        }
    }

    private static function sanitizeFileName($str) {
        // get rid of consecutive dots
        $str = preg_replace('/\.\.+/', '.', $str);
        // get rid of trailing dots
        $str = preg_replace('/\.+$/', '', $str);
        // get rid of leading dots
        $str = preg_replace('/^\.+/', '', $str);
        // get rid of other nasty characters
        return preg_replace('/[^0-9a-zA-Z_\.-]/', '_', $str);
    }

    public function getUpload($key) {
        $file = null;
        if (isset($_FILES[$key])) {

            $tmp_name = $_FILES[$key]['tmp_name'];
            $nameOnDisk = $this -> generateName();
            $path = $this -> dir . DIRECTORY_SEPARATOR . $nameOnDisk;
            $success = move_uploaded_file($tmp_name, $path);
            if (!$success) {
                throw new Exception("Problem getting uploaded file");
            }
            // @formatter:off
            $params = array(
                'Directory' => $this->dir,
                'DiskName' => $nameOnDisk,
                'OrigName' => self::sanitizeFileName($_FILES[$key]['name']),
                'Type' => $_FILES[$key]['type'],
                'Size' => $_FILES[$key]['size']
            );
            // @formatter:on
            $file = new File($params);
        }
        return $file;
    }

    private function generateName() {
        do {
            $name = uniqid('upload');
        } while (is_file($this->dir . DIRECTORY_SEPARATOR . $name));
        return $name;
    }

    public function getAllUploads() {
        $result = array();
        foreach ($_FILES as $key => $meta) {
            $result[] = $this -> getUpload($key);
        }
        return $result;
    }
}
?>