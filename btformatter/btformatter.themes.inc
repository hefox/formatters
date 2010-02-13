<?php

function theme_btimageformatter_formatter_cache($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  $matches = array();
  preg_match('/(?P<presetname>\w+)_btimageformatter/', $element['#formatter'], $matches);
  $presetname = $matches['presetname'];
  
  $item = $element['#item'];
  
  $item['data']['alt'] = isset($item['data']['alt']) ? $item['data']['alt'] : '';
  $item['data']['title'] = isset($item['data']['title']) ? $item['data']['title'] :NULL;

  $imagetag = theme('imagecache', $presetname, $item['filepath'], $item['data']['alt'], $item['data']['title']); 
  // Render items.
  $class = "btformatter btimagecache btimagecache-$presetname btimagecache-$style btimagecache-{$element['#formatter']}";
  $id = btformatter_set_bt(url('btformatter/'.$element['#node']->nid));
  return l($imagetag, 'node/'.$element['#node']->nid, array('attributes' => array('class' => $class, 'id' => $id), 'html' => TRUE));
}

function theme_btimageformatter_formatter_reg($element) {
  if (empty($element['#item']['fid'])) {
    return '';
  }
  
  $item['data']['title'] = isset($item['data']['title']) ? $item['data']['title'] : NULL;
  
  $imagetag = theme('imagefield_formatter_image_plain', $element);
  
  $class = 'btformatter imagefield imagefield-nodelink imagefield-'. $element['#field_name'];
  $id = btformatter_set_bt(url('btformatter/'.$element['#node']->nid));
  return l($imagetag, 'node/'.$element['#node']->nid, array('attributes' => array('class' => $class, 'id' => $id), 'html' => TRUE));
}

function btformatter_set_bt($url) {
  static $i = 0;
    $i++;
      $options['btformatter'] = array(
      'cssSelect' => '#btformatter-'.$i,
      'ajaxPath' => $url,
    );
    beautytips_add_beautytips($options);
    return 'btformatter-'.$i;
}
