<?php

/**
 * @file
 * Contains PerformanceTestRender class to compare approaches of render engine.
 */

$plugin = array(
  'name' => 'Render with cache',
  'description' => 'Provides the test to compare render performance.',
  'handler' => array(
    'class' => 'PerformanceTestRenderCache',
  ),
);

class PerformanceTestRenderCache implements PerformanceTestInterface {

  /**
   * The plugin definition for this instance.
   */
  protected $plugin;

  /**
   * The amount of iterations for the test.
   */
  public $iterations = 10000;

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
      'renderWithoutCache',
      'renderWithCache',
    );
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function renderWithoutCache($n) {
    $variant = performance_test_get_default_variant_array('Without cache', 'Do not use tag for any markup');

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

    return $variant;
  }

  /**
   * The callback function with used to export results to a page.
   */
  public function renderWithCache($n) {
    $variant = performance_test_get_default_variant_array('With cache', 'Use markup for to output simple content');

    $page['highlighted']['new_stuff'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => 'my-container'),
      '#cache' => array(
        'keys' => array('render_example', 'cache', 'demonstration'),
        'bin' => 'cache',
        'expire' => time() + 100,
        'granularity' => DRUPAL_CACHE_PER_PAGE | DRUPAL_CACHE_PER_ROLE,
      ),
    );

    $text = t('Heading');
    for ($i = 0; $i < $n; $i++) {
      $page['highlighted']['new_stuff'][$i] = array(
        '#markup' => '<h2 class="my-heading">' . $text . '</h2>',
      );
    }

    drupal_render($page);

    return $variant;
  }

  /**
   * Each of test can specify a category where it will be appeared.
   */
  public function testCategory() {
    $types = performance_test_get_available_categories();
    return $types[0]['type_name'];
  }
}
