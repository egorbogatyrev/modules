<?php

/**
 * @file
 * Contains PerformanceTestRender class to compare approaches of render engine.
 */

$plugin = array(
  'name' => 'Access callback with loading node',
  'description' => 'Provides the test to compare access callbacks performance.',
  'handler' => array(
    'class' => 'PerformanceTestCustomAccessCallback',
  ),
);

class PerformanceTestCustomAccessCallback implements PerformanceTestInterface {

  /**
   * The plugin definition for this instance.
   */
  protected $plugin;

  /**
   * The amount of iterations for the test.
   */
  public $iterations = 1000;

  /**
   * Constructor for the report plugin class.
   */
  public function __construct($plugin) {
    $this->plugin = $plugin;
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function exportResults() {
    return array(
      'accessWithLoadFullObject',
      'accessWithoutObject',
    );
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function accessWithLoadFullObject($n) {
    $variant = performance_test_get_default_variant_array('Load node object', 'Load the full node object for getting some params');
//    $method = __METHOD__;
    for ($i = 0; $i < $n; $i++) {
//      $uid = db_query("SELECT uid FROM node WHERE nid = 1")->fetchField();
      $node = node_load(1);
      $author = $node->uid;
    }

    return $variant;
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function accessWithoutObject($n) {
    $variant = performance_test_get_default_variant_array('Without loading', 'Get uid by db query');

    for ($i = 0; $i < $n; $i++) {
      $query = db_select('node', 'n');
      $query->fields('n', array('uid'));
      $query->condition('n.nid', 1);
      $author = $query->execute()->fetchField();
    }

    return $variant;
  }

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function testCategory() {
    $types = performance_test_get_available_categories();
    return $types[2]['type_name'];
  }
}
