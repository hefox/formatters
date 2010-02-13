<?php

function btformatter_views_data() {
  $data['node']['bt_node_link'] = array(
    'field' => array(
      'title' => t('Node link with beauty tip'),
      'help' => t('Provide a simple link to view the node, with beauty tip.'),
      'handler' => 'views_handler_field_node_link_bt',
    ),
  );
  return $data;
}


function btformatter_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'btformatter') ,
    ),
    'handlers' => array(
      // field handlers
      'views_handler_field_node_link_bt' => array(
        'parent' => 'views_handler_field_node_link',
      ),
    )
  );
}
