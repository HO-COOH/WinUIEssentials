#pragma once

/**
 * @brief This is a workaround for `ListViewBase` incorrect `SelectedIndex`, the issue is recorded here: https://github.com/microsoft/microsoft-ui-xaml/issues/8257. 
 * To use this workaround, inherit from this class in the implementation, see Segmented.h
 * @tparam DerivedT 
 */
template<typename DerivedT>
struct ListViewBaseWorkaround : DerivedT
{
private:
    int m_internalSelectedIndex = -1;
    bool m_templateApplied{};
public:
    int SelectedIndex()
    {
        return m_internalSelectedIndex;
    }

    /**
     * @brief call this on the last line of `OnApplyTemplate()`
     *
     * @details We already know that `SelectedIndex` is correct when the first `onSelectedIndexChanged` is called,
     * and then become incorrect when `OnApplyTemplate()` is called. So We just record the first correct `SelectedIndex`
     * (this is achieved by this `onSelectedIndexChanged()`, and then set it in `OnApplyTemplate`
     */
    void TemplateApplied()
    {
        //This is the workaround
        if (!m_templateApplied)
        {
            //See https://github.com/CommunityToolkit/Windows/pull/699
            DerivedT::SelectedIndex(-1);
            DerivedT::SelectedIndex(m_internalSelectedIndex);
        }
        m_templateApplied = true;


        /*
            When this bug get fixed by WinUI, comment the above workaround,
            and uncomment below to apply the `SelectedIndex` to highlight the correct `SegmentedItem`
        */
        //DerivedT::onSelectedIndexChanged(nullptr, nullptr);
    }

    /**
     * @brief Call this on the first line of `onSelectedIndexChanged` in `Segmented::onSelectedIndexChanged`
     */
    void onSelectedIndexChanged()
    {
        if (auto const selectedIndex = DerivedT::SelectedIndex(); ((m_internalSelectedIndex == -1 && selectedIndex > -1) || m_templateApplied))
            m_internalSelectedIndex = selectedIndex;
    }
};