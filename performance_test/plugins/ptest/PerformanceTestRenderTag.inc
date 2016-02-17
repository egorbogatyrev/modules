<?php

/**
 * @file
 * Contains PerformanceTestRender class to compare approaches of render engine.
 */

$plugin = array(
  'name' => 'Theme',
  'description' => 'Provides the test to compare render performance.',
  'handler' => array(
    'class' => 'PerformanceTestRender',
  ),
);

class PerformanceTestRenderTag implements PerformanceTestInterface {

  /**
   * The plugin definition for this instance.
   */
  protected $plugin;

  /**
   * The amount of iterations for the test.
   */
  public $limit = 50;

  /**
   * Constructor for the report plugin class.
   */
  public function __construct($plugin) {
    $this->plugin = $plugin;
  }

  /**
   * The report machine name.
   */
  public static function testMachineName() {

  }

  /**
   * Returns a permission for the report.
   */
  public function testPermission() {

  }

  /**
   * The report description.
   */
  public function testDescription() {

  }

  /**
   * The callback function with used to export results to a page.
   */
  public function exportResults() {
    return array(
      'renderWithTag',
      'renderWithMarkup',
    );
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function renderWithTag($n) {
    $variant = performance_test_get_default_variant_array('Extra tag using', 'Do not use tag for any markup');

    $page['highlighted']['new_stuff'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => 'my-container'),
    );

    $text = t('Heading');
    for ($i = 0; $i < $n; $i++) {
      $page['highlighted']['new_stuff'][$i] = array(
        '#type' => 'html_tag',
        '#tag' => 'h2',
        '#value' => $text,
        '#attributes' => array('class' => 'my-heading'),
      );
    }

    drupal_render($page);

    return $variant;
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function renderWithMarkup($n) {
    $variant = performance_test_get_default_variant_array('Markup using', 'Use markup for to output simple content');

    $page['highlighted']['new_stuff'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => 'my-container'),
    );

    $text = t('Heading');
    for ($i = 0; $i < $n; $i++) {
      $page['highlighted']['new_stuff'][$i] = array(
        '#markup' => '<h2 class="my-heading">' . $text . '</h2>',
      );
    }

    drupal_render($page);

    return (timer_read('2') / 1000);
  }

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function testCategory() {
    $types = performance_test_get_available_categories();
    return $types[0]['type_name'];
  }
}
