<?php

function theme_filefieldlink_formatter_link($element) {
  $file = $element['#item'];
  $field = content_fields($element['#field_name']);
  $output = theme('filefieldlink_item', $file, $field);
  return $output;
}


function theme_filefieldlink_formatter_nodelink($element) {
  $file = $element['#item'];
  $field = content_fields($element['#field_name']);
  if (empty($file['data']['description'])) {
    $file['data']['description'] = $element['#node']->title? $element['#node']->title : 
      ($element['#node']->nid ?
      db_result(db_query("SELECT title from {node} where nid=%d",
      $element['#node']->nid))
      :'');
  }
  $output = theme('filefieldlink_item', $file, $field);
  return $output;
}


function theme_filefieldlink_formatter_nodelink_always($element) {
  $file = $element['#item'];
  $field = content_fields($element['#field_name']);
  $file['data']['description'] = $element['#node']->title? $element['#node']->title : 
    ($element['#node']->nid ?
    db_result(db_query("SELECT title from {node} where nid=%d",$element['#node']->nid)):'');
  $output = theme('filefieldlink_item', $file, $field);
  return $output;
}

function theme_filefieldlink_item($file, $field) {
  if (filefield_view_access($field['field_name'])) {
    return theme('filefieldlink_file', $file);
  }
  return '';
}


function theme_filefieldlink_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  if ($file['display_icon']) $icon = theme('filefieldlink_icon', $file);

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described 
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'] . '; length=' . $file['filesize'],
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

  if (!empty($icon)) return '<div class="filefield-file clear-block">'. $icon . l($link_text, $url, $options) .'</div>';
  else return l($link_text, $url, $options);
}
